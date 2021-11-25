#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix/matrix.h"
#include "edge/edge.h"
#include "vector/vector.h"

/* Predpokladana delka radky */
#define LINE_LEN 8192
#define DELIMITER ","

#define IS_VALID "True"


int check_vector_node_duplicates(const vector_t *v, const int id) {
    int i;
    for (i = 0; i < v->count; ++i) {

        if (*(int *)vector_at(v, i) == id){
            return 1;
        }
    }
    return 0;
}


int check_vector_edge_duplicates(const vector_t *v, const int id) {
    int i;
    for (i = 0; i < v->count; ++i) {

        if ((*(edge *)vector_at(v, i)).id == id){
            return 1;
        }
    }
    return 0;
}


vector_t * load_nodes(const char *file_name) {
    /* Souborovy vstup/vystup */
    FILE *fr;
    char line[LINE_LEN];
    /* pole vsech uzlu, defaultne nastaveno na "4" prvky, bude se zvetsovat*/
    vector_t *nodes;

    if (!file_name)
        return NULL;



    //otevreni souboru
    fr = fopen(file_name, "r");
    if (fr == NULL) {
        printf("No Such File !! ");
        return NULL;
    }


    nodes = vector_create(sizeof(int *), NULL);
    if (!nodes) {
        vector_destroy(&nodes);
        fclose(fr);
        return NULL;
    }

    /* vynulovani znaku v pameti "line" */
    memset(line, 0, LINE_LEN);



    while (fgets(line, LINE_LEN, fr)) {

        // pokud line obsahuje "id", automaticky se rozumi, ze jde o prvni radku, rovnou se preskoci
        if (strstr(line, "id") == NULL){
//            printf("%s\n" de)
            char *token;
             token = strtok(line, DELIMITER);
            if (token != NULL) {
                int tmp , check;
                tmp = atoi(token);

                check = check_vector_node_duplicates(nodes, tmp);
//                printf("%d\n",tmp);
                if (check == 0){
                    if (vector_push_back(nodes, &tmp) == INVALID_INDEX) {
                        vector_destroy(&nodes);
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


    return nodes;

}


vector_t * load_edges(const char *file_name, const int isValid) {
    /* Souborovy vstup/vystup */
    FILE *fr;
    char line[LINE_LEN];
    edge *e;

    vector_t *temps;

    if (!file_name) {
        return NULL;
    }

    memset(line, 0, LINE_LEN);

    temps = vector_create(sizeof(edge *), (vec_it_dealloc_t)edge_destroy);
    if(!temps) {
        return NULL;
    }

    //otevreni souboru
    fr = fopen(file_name, "r");
    if (fr == NULL) {
        printf("No Such File !! ");
        return NULL;
    }


    while (fgets(line, LINE_LEN, fr)) {
        // pokud line obsahuje "id", automaticky se rozumi, ze jde o prvni radku, rovnou se preskoci
        if (strstr(line, "id,source") == NULL) {
            if (isValid == 0 && !strstr(line, "False")) { // prepinac "-a"
                printf("%s\n\n", line);
                 continue;
            }
            char *token;
            int edge_id, check;

            token = strtok(line, DELIMITER);
            edge_id = atoi(token);
            check = check_vector_edge_duplicates(temps, edge_id);

            if (check == 0){
                e = edge_create(line);
                if (!e || vector_push_back(temps, &e) == INVALID_INDEX) {
                    vector_destroy(&temps);
                    fclose(fr);
                    return NULL;
                }

            }

            e = edge_create(line);
            if (!e) {
                return NULL;
            }

            if (vector_push_back(temps, edge_create(line)) == INVALID_INDEX){
                return NULL;
            }


        }
        memset(line, 0, LINE_LEN);
    }

    if (fclose(fr) == EOF)
    {
        printf("Soubor pro cteni se nepodarilo uzavrit.");
        return NULL;
    }

    return temps;
}


int main(int argc, char *argv[]) {


    vector_t *list_nodes;
    vector_t *list_edges;
    matrix *m_capacities;
    matrix *m_edges;


    list_nodes = load_nodes("./data/plzen/pilsen_nodes.csv");
//    list_nodes = load_nodes("./data/example/example_nodes.csv");
//    for (int i = 0; i < vector_count(list_nodes); i++)
//        printf("%d\n", *(int *)vector_at(list_nodes, i));
    if (!list_nodes) {
        printf("Invalid vertex file.\n");
        return 1;
    }

//    list_edges = load_edges("./data/plzen/pilsen_edges.csv");
    list_edges = load_edges("./data/example/example_edges.csv", 0);
    for (int i = 0; i < vector_count(list_edges); i++)
        printf("%d\n", (*(edge *)vector_at(list_edges, i)).id);
    if (!list_edges) {
        printf("Invalid edges file.\n"); //TODO check
        return 6;
    }
//    m_edges = matrix_create(nodes_count, nodes_count, 0);
//    m_capacities = matrix_create(nodes_count, nodes_count, 0);
//
//    if (!m_capacities, !m_edges) {
//        printf("Matrix not created");
//        return -1;
//    }

//    matrix_fill_edges(m_capacities, m_edges, list_edges);
    // uvolneni pameti list_nodes
    vector_destroy(&list_nodes);
    // uvolneni pameti edges
//    edge_free(&list_edges);

//    matrix_free(&m_edges);
//    matrix_free(&m_capacities);

    return 0;
}
