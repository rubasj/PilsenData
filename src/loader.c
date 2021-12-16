#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix/matrix.h"

#include "max_flow/algorithm.h"

/* Predpokladana maximalni delka radky */
#define LINE_LEN 8192
#define DELIMITER ","
#define CSV ".csv"


/**
 * Funkce pro zapisovani hran do souboru, nejdrive najde hranu a pak ji vypise
 * @param edges vector obsahujici hrany
 * @param min_cut vector obsahujici id hran minimalniho rezu
 * @param file soubor, do ktereho se bude ukladat
 * @return
 */
int print_output(const vector_t *edges, const vector_t *min_cut, const char *file) {
    FILE *fw;
    size_t i;
    edge *e;
    int id;

    if (!edges || !min_cut || !file || strstr(file, CSV) == NULL) {
        return 0;
    }

    fw = fopen(file, "w");



    /* zjisteni zda se soubor pro zapis otevrel */
    if (fw == NULL) {
        printf("Vystupni soubor se nepodarilo otevrit");
        return 0;
    }


    for (i = 0; i < vector_count(min_cut); i++) {

        id = *(int *)vector_at(min_cut, i);
        e = find_edge_by_id(edges, id);

        fputs(e->description, fw);

    }
    /* Uzavreni souboru  fw */
    if (fclose(fw) == EOF) {
        printf("Soubor pro zapis se nepodarilo uzavrit (fsm.c)");
        return 0;
    }

    return 1;
}

/**
 * Kontrola zda uzel jiz existuje
 * @param vertexes vektor uzlu
 * @param id
 * @return
 */
int check_vector_vertex_duplicates(const vector_t *vertexes, const int id) {
    size_t i;

    if (!vertexes) {
        return -1;
    }
    for (i = 0; i < vector_count(vertexes); ++i) {

        if (*(int *)vector_at(vertexes, i) == id){
            return 1;
        }
    }
    return 0;
}

/**
 * Kontrola, hrana se stejnym ID jiz existuje
 * @param edges vector, ve kterem chceme hledat
 * @param id id vektoru
 * @return pokud existuje, vrati 1, jinak 0
 */
int check_vector_edge_duplicates(const vector_t *edges, const int id) {
    size_t i;

    if (!edges) {
        return -1;
    }

    for (i = 0; i < vector_count(edges); ++i) {

        if ((*(edge **)vector_at(edges, i))->id == id){
            return 1;
        }
    }
    return 0;
}

/**
 * Nacteni uzlu ze souboru
 * @param file_name nazev souboru
 * @return pointer na vector uzlu
 */
vector_t *load_vertexes(const char *file_name) {
    /* Souborovy vstup/vystup */
    FILE *fr;
    char line[LINE_LEN];
    /* pole vsech uzlu, defaultne nastaveno na "4" prvky, bude se zvetsovat*/
    vector_t *vertexes;

    if (!file_name || strstr(file_name, CSV) == NULL) {
        return NULL;
    }

    /*otevreni souboru*/
    fr = fopen(file_name, "r");
    if (fr == NULL) {
        return NULL;
    }

    vertexes = vector_create(sizeof(int *), NULL);
    if (!vertexes) {
        vector_destroy(&vertexes);
        fclose(fr);
        return NULL;
    }

    /* vynulovani znaku v pameti "line" */
    memset(line, 0, LINE_LEN);

    while (fgets(line, LINE_LEN, fr)) {

        /* pokud line obsahuje "id", automaticky se rozumi, ze jde o prvni radku, rovnou se preskoci */
        if (strstr(line, "id") == NULL){
            char *token;

            token = strtok(line, DELIMITER);
            if (token != NULL) {
                int tmp , check;
                tmp = atoi(token);

                check = check_vector_vertex_duplicates(vertexes, tmp);
                if (check == 0){
                    if (vector_push_back(vertexes, &tmp) == INVALID_INDEX) {
                        vector_destroy(&vertexes);
                        fclose(fr);
                        return NULL;
                    }
                }

            }

        }
        memset(line, 0, LINE_LEN);
    }

    if (fclose(fr) == EOF)
    {
        printf("Soubor pro cteni se nepodarilo uzavrit.");
        return NULL;
    }


    return vertexes;

}

/**
 * Funkce nacte hrany (edges)
 * @param file_name - nazev souboru (popripade cesta) k datum o hranach
 * @param switcher 0 - pokud akceptuje jen True hrany, 1 - pokud akceptuje vsechny
 * @return vrati pointer na vector hran
 */
vector_t * load_edges(const char *file_name, const int switcher) {
    /* Souborovy vstup/vystup */
    FILE *fr;
    char line[LINE_LEN];
    edge *e;

    vector_t *temps;

    if (!file_name || strstr(file_name, CSV) == NULL) {
        return NULL;
    }

    memset(line, 0, LINE_LEN);

    temps = vector_create(sizeof(edge *), (vec_it_dealloc_t)edge_destroy);
    if(!temps) {
        return NULL;
    }

    /*otevreni souboru*/
    fr = fopen(file_name, "r");
    if (fr == NULL) {
        return NULL;
    }

    while (fgets(line, LINE_LEN, fr)) {
        /* pokud line obsahuje "id", automaticky se rozumi, ze jde o prvni radku, rovnou se preskoci */
        if (strstr(line, "id,source") == NULL) {
            if (switcher == 0 &&
            strstr(line, "False" ) != NULL){
                continue;
            }
            e = edge_create(line);

            if (!e) {
                vector_destroy(&temps);
                fclose(fr);
                return NULL;
            }
            if (check_vector_edge_duplicates(temps, e->id) == 0) {
                vector_push_back(temps, &e);
            }

        }

    }

    if (fclose(fr) == EOF)
    {
        printf("Soubor pro cteni se nepodarilo uzavrit.");
        return NULL;
    }

    return temps;
}

/**
 * Funkce najde index nodu, kde se nachazi ve vektoru
 * @param nodes vector nodes
 * @param node_id node, jehoz index hledame
 * @return kdyz node je v zaznamu, vrati se jeho index, jinak -1
 */
int find_vertex_position_in_vector(const vector_t *nodes, int node_id) {

    size_t i;

    for (i = 0;  i < vector_count(nodes); i++) {
        if ((*(int *)vector_at(nodes, i)) == node_id)
            return i;
    }

    return -1;
}


/**
 * Vychozi funkce programu
 * @param argc pocet zadanych parametru v prikazove radce
 * @param argv pointer na argumenty prikazoveho radku
 * @return vysledek programu
 */
int main(int argc, char **argv) {
    /* pokud je switcher == 1, budeme brat taky jeste neexistujici useky silnic */
    int switcher, out_active, source_id, target_id, sink, i, source, result;
    char *vertex_file, *edge_file, *output_file;
    vector_t *list_vertexes, *min_cut, *list_edges;
    matrix *m_capacities, *m_edges;

    if (argc <= 9) {
        printf("Usage: Missing arguments.");
        return EXIT_FAILURE;
    }

    out_active = 0;
    switcher = 0;
    /* argv[0] vzdy obsahuje nazev binarniho souboru */
    for (i = 1; i < argc; i++) {

        /* nacitani souboru s nodes */
        if (strcmp(argv[i], "-v") == 0) {
            vertex_file = argv[i + 1];
            continue;
        }
        /* nacitani souboru s edges */
        if (strcmp(argv[i], "-e") == 0) {
            edge_file = argv[i + 1];
            continue;
        }

        /* source id*/
        if (strcmp(argv[i], "-s") == 0) {
            source_id = atoi(argv[i + 1]);
            continue;
        }
        /* target id */
        if (strcmp(argv[i], "-t") == 0) {
            target_id = atoi(argv[i + 1]);
            continue;
        }
        /* nastaveni vystupu */
        if (strcmp(argv[i], "-out") == 0) {
            out_active = 1;
            output_file = argv[i + 1];
            continue;
        }

        /* prepinac, zda ma program pocitat i neexistujici edge */
        if (strcmp(argv[i], "-a") == 0) {
            switcher = 1;
            continue;
        }
    }

    if (!vertex_file || !edge_file || (!output_file && out_active != 0)){
        printf("Missing arguments.\n");
        return EXIT_FAILURE;
    }



    list_vertexes = load_vertexes(vertex_file);
    if (!list_vertexes) {
        vector_destroy(&list_vertexes);
        printf("Invalid vertex file.\n");
        return 1; /* dle zadani */
    }

    list_edges = load_edges(edge_file, switcher);

    if (!list_edges) {
        vector_destroy(&list_vertexes);
        vector_destroy(&list_edges);
        printf("Invalid edges file.\n");
        return 6; /*dle zadani*/
    }

    /* vytvoreni matic obsahujici id a kapacity hran v grafu */
    m_edges = matrix_create(vector_count(list_vertexes), vector_count(list_vertexes), -1); /* -1 hrana mezi nody neexistuje */
    m_capacities = matrix_create(vector_count(list_vertexes), vector_count(list_vertexes), 0); /* 0 neni zadna kapacita (neexistuje node) */

    if (!m_capacities || !m_edges) {
        vector_destroy(&list_vertexes);
        vector_destroy(&list_edges);
        printf("Matrix not created.");
        return EXIT_FAILURE;
    }


    sink = find_vertex_position_in_vector(list_vertexes, target_id);
    if (sink == -1) {

        printf("Invalid sink vertex.\n");
        return 4; /* dle zadani */
    }

    matrix_fill_edges(m_capacities, m_edges, list_vertexes, list_edges);

    source = find_vertex_position_in_vector(list_vertexes, source_id);
    if (source == -1) {


        printf("Invalid source vertex.\n");
        return 3; /* dle zadani */
    }

    /* uloziste hran minimalniho rezu */
    min_cut = vector_create(sizeof(int *), NULL);

    /* result (max flow) */
    result = ford_fulkerson(m_capacities, m_edges, source, sink, out_active, min_cut);

    /* pokud v siti neexistuje tok nenulove velikosti program konci 6 */
    if (result <= 0) {

        vector_destroy(&list_vertexes);
        vector_destroy(&list_edges);
        matrix_free(&m_edges);
        matrix_free(&m_capacities);
        vector_destroy(&min_cut);

        return 6; /* dle zadani */
    }
    /* pokud je output v parametrech, udela zapis do souboru */
    if (out_active == 1) {
        if (print_output(list_edges, min_cut, output_file) == 0) {
            vector_destroy(&list_vertexes);
            vector_destroy(&list_edges);
            matrix_free(&m_edges);
            matrix_free(&m_capacities);
            vector_destroy(&min_cut);
            return 5;
        }
    }


    vector_destroy(&list_vertexes);
    vector_destroy(&list_edges);
    matrix_free(&m_edges);
    matrix_free(&m_capacities);
    vector_destroy(&min_cut);

    return EXIT_SUCCESS;
}


