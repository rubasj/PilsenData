/**
 * Vychozi soubor celeho projektu
 * @author Jan Rubas
 * @email janrubas@students.zcu.cz
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix/matrix.h"

#include "max_flow/algorithm.h"


/* Predpokladana maximalni delka radky, kterou lze nacist */
#define LINE_LEN 8192
/* oddelovac */
#define DELIMITER ","
/* csv koncovka souboru */
#define CSV ".csv"
/* pouze indikace, ze promenna je neurcena */
#define EMPTY_INT -1


/* return hodnoty dle zadani, kdyz se vyskytne chyba, detail je v nazvu */
#define INVALID_VERTEX_FILE 1
#define INVALID_EDGE_FILE 2
#define INVALID_SOURCE_VERTEX 3
#define INVALID_SINK_VERTEX 4
#define INVALID_OUTPUT_FILE 5
#define EMPTY_MAX_FLOW 6

/* Hlavicky, ktere musi byt pri nacitani souboru */
#define EDGES_HEADER "id,source,target,capacity,isvalid,WKT"
#define VERTICES_HEADER "id,WKT"
/* Kontrola pro funkce, ktere vraci hodnoty a nemaji pridelene ukonceni programu dle zadani*/
#define FUNCTION_FAILURE 1
#define FUNCTION_OK 0


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
        return INVALID_OUTPUT_FILE;
    }

    fw = fopen(file, "w");

    if (!strstr(file, CSV)) {
        return INVALID_OUTPUT_FILE;
    }
    /* zjisteni zda se soubor pro zapis otevrel */
    if (fw == NULL) {
        printf("Vystupni soubor se nepodarilo otevrit");
        return INVALID_OUTPUT_FILE;
    }


    fputs( EDGES_HEADER, fw);
    fputs( "\n", fw);
    for (i = 0; i < vector_count(min_cut); i++) {

        id = *(int *)vector_at(min_cut, i);
        e = find_edge_by_id(edges, id);


        fputs(e->description, fw);
/*        edge_destroy(&e); */
    }


    /* Uzavreni souboru  fw */
    if (fclose(fw) == EOF) {
        printf("Soubor pro zapis se nepodarilo uzavrit (fsm.c)");
        return INVALID_OUTPUT_FILE;
    }

    return FUNCTION_OK;
}

/**
 * Kontrola zda uzel jiz existuje
 * @param vertices vektor uzlu
 * @param id identifikator pro porovnani
 * @return vrati 0, pokud jeste vrchol s timto ID neexistuje, jinak 1
 */
int check_vector_vertex_duplicates(const vector_t *vertices, const int id) {
    size_t i;

    if (!vertices) {
        return FUNCTION_FAILURE;
    }
    for (i = 0; i < vector_count(vertices); ++i) {

        if (*(int *)vector_at(vertices, i) == id){
            return FUNCTION_FAILURE;
        }
    }
    return FUNCTION_OK;
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
        return FUNCTION_FAILURE;
    }

    for (i = 0; i < vector_count(edges); ++i) {

        if ((*(edge **)vector_at(edges, i))->id == id){
            return FUNCTION_FAILURE;
        }
    }
    return FUNCTION_OK;
}

/**
 * Nacteni uzlu ze souboru
 * @param file_name nazev souboru
 * @return pointer na vector uzlu
 */
vector_t *load_vertices(const char *file_name) {
    /* Souborovy vstup/vystup */
    FILE *fr;
    char *line;
    /* pole vsech uzlu, defaultne nastaveno na "4" prvky, bude se zvetsovat*/
    vector_t *vertices;

    line = (char *) malloc(LINE_LEN * sizeof(char));
    if (!line) {
        return NULL;
    }
    memset(line, 0, LINE_LEN * sizeof(char));
    if (!file_name || strstr(file_name, CSV) == NULL) {
        free(line);
        return NULL;
    }

    /*otevreni souboru*/
    fr = fopen(file_name, "r");
    if (fr == NULL) {
        free(line);
        return NULL;
    }

    vertices = vector_create(sizeof(int *), NULL);
    if (!vertices) {
        free(line);
        vector_destroy(&vertices);
        fclose(fr);
        return NULL;
    }

    /* vynulovani znaku v pameti "line" */
    memset(line, 0, LINE_LEN * sizeof(char));

    if (fgets(line, LINE_LEN, fr)) {
        if (strstr(line, VERTICES_HEADER) == NULL) {
            vector_destroy(&vertices);
            free(line);
            return NULL;
        }
    }
    memset(line, 0, LINE_LEN * sizeof(char));
    while (fgets(line, LINE_LEN, fr)) {


        /* pokud line obsahuje "id", automaticky se rozumi, ze jde o prvni radku, rovnou se preskoci */
        if (strstr(line, VERTICES_HEADER) == NULL){
            char *token;

            token = strtok(line, DELIMITER);
            if (token != NULL) {
                int tmp , check;
                tmp = atoi(token);

                check = check_vector_vertex_duplicates(vertices, tmp);
                if (check == 0){
                    if (vector_push_back(vertices, &tmp) == INVALID_INDEX) {
                        vector_destroy(&vertices);
                        fclose(fr);
                        return NULL;
                    }
                }

            }

        }
        memset(line, 0, LINE_LEN * sizeof(char));
    }

    free(line);
    if (fclose(fr) == EOF)
    {
        printf("Soubor pro cteni se nepodarilo uzavrit.");
        return NULL;
    }


    return vertices;

}

/**
 * Funkce nacte hrany (edges)
 * @param file_name - nazev souboru (popripade cesta) k datum o hranach
 * @param switcher 0 - pokud akceptuje jen True hrany, 1 - pokud akceptuje vsechny
 * @return vrati pointer na vector hran
 */
vector_t *load_edges(const char *file_name, const int switcher) {
    /* Souborovy vstup/vystup */
    FILE *fr;
    char *line;
    edge *e;
    vector_t *temps;

    if (!file_name || strstr(file_name, CSV) == NULL) {
        return NULL;
    }

    line = (char *) malloc(LINE_LEN * sizeof(char));

    if (!line) {
        return NULL;
    }

    memset(line, 0, LINE_LEN * sizeof(char));

    temps = vector_create(sizeof(edge *), (vec_it_dealloc_t)edge_destroy);

    if(!temps) {
        free(line);
        return NULL;
    }

    /*otevreni souboru*/
    fr = fopen(file_name, "r");
    if (fr == NULL) {
        return NULL;
    }

    if (fgets(line, LINE_LEN, fr)) {
        if (strstr(line, EDGES_HEADER) == NULL) {
            vector_destroy(&temps);
            free(line);
            return NULL;
        }
    }

    memset(line, 0, LINE_LEN * sizeof(char));
    while (fgets(line, LINE_LEN, fr)) {


        /* pokud line obsahuje "id", automaticky se rozumi, ze jde o prvni radku, rovnou se preskoci */
        if (strstr(line, EDGES_HEADER) == NULL) {
            if (switcher == 0 &&
            strstr(line, "False" ) != NULL){
                memset(line, 0, LINE_LEN * sizeof(char));
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
        memset(line, 0, LINE_LEN * sizeof(char));
    }

    free(line);

    if (fclose(fr) == EOF)
    {
        printf("Soubor pro cteni se nepodarilo uzavrit.");
        return NULL;
    }

    return temps;
}


/**
 * Vychozi funkce programu
 * @param argc pocet zadanych parametru v prikazove radce
 * @param argv pointer na argumenty prikazoveho radku
 * @return vysledek programu
 */
int main(int argc, char **argv) {
    /* pokud je switcher == 1, budeme brat taky jeste neexistujici useky silnic */
    int switcher, out_active, source_id, target_id, i, result, sink, source;
    char *vertex_file, *edge_file, *output_file;
    vector_t *list_vertices, *min_cut, *list_edges;
    matrix *m_capacities, *m_edges;


#define CLEAR                    \
    vector_destroy(&list_vertices);\
    vector_destroy(&list_edges);   \
    matrix_free(&m_edges);         \
    matrix_free(&m_capacities);    \
    vector_destroy(&min_cut);


    out_active = EMPTY_INT;
    switcher = EMPTY_INT;
    /* argv[0] vzdy obsahuje nazev binarniho souboru */
    for (i = 1; i < argc; i++) {

     /*   printf("%s \n",argv[i]);*/
        /* nacitani souboru s uzly */
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

    list_vertices = load_vertices(vertex_file);
    if (!list_vertices) {
        printf("Invalid vertex file.\n");
        return INVALID_VERTEX_FILE; /* dle zadani */
    }

    list_edges = load_edges(edge_file, switcher);

    if (!list_edges) {
        vector_destroy(&list_vertices);
        printf("Invalid edges file.\n");
        return INVALID_EDGE_FILE; /*dle zadani*/
    }

    /* vytvoreni matic obsahujici id a kapacity hran v grafu */
    m_edges = matrix_create(vector_count(list_vertices), vector_count(list_vertices), -1); /* -1 hrana mezi nody neexistuje */
    if (!m_edges) {
        vector_destroy(&list_edges);
        vector_destroy(&list_vertices);

        printf("Matrix not created.");
        return EXIT_FAILURE;
    }
    m_capacities = matrix_create(vector_count(list_vertices), vector_count(list_vertices), 0); /* 0 neni zadna kapacita (neexistuje uzel) */

    if (!m_capacities) {
        matrix_free(&m_edges);
        vector_destroy(&list_edges);
        vector_destroy(&list_vertices);
        printf("Matrix not created.");
        return EXIT_FAILURE;
    }


    sink = get_vertex_position(list_vertices, target_id);
    if (sink < 0) {
        matrix_free(&m_capacities);
        matrix_free(&m_edges);
        vector_destroy(&list_edges);
        vector_destroy(&list_vertices);
        printf("Invalid sink vertex.\n");
        return INVALID_SINK_VERTEX;
    }



    source = get_vertex_position(list_vertices, source_id);
    if (source < 0) {
        matrix_free(&m_capacities);
        matrix_free(&m_edges);
        vector_destroy(&list_edges);
        vector_destroy(&list_vertices);
        printf("Invalid source vertex.\n");
        return INVALID_SOURCE_VERTEX;
    }
    matrix_fill_edges(m_capacities, m_edges, list_vertices, list_edges);

    /* uloziste hran minimalniho rezu */
    min_cut = vector_create(sizeof(int *), NULL);

    /* result (max flow) */
    result = ford_fulkerson(m_capacities, m_edges, source, sink, out_active, min_cut);

    /* pokud v siti neexistuje tok nenulove velikosti program konci 6 */
    if (result <= 0) {
        CLEAR

        return EMPTY_MAX_FLOW;
    }
    /* pokud je output v parametrech, udela zapis do souboru */
    if (out_active == 1) {
        if (print_output(list_edges, min_cut, output_file) != EXIT_SUCCESS) {
            CLEAR
            return INVALID_OUTPUT_FILE;
        }
    }
    printf("Max network flow is |x| = %d.\n", result);

    CLEAR

    return EXIT_SUCCESS;
}


