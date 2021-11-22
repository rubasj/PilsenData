#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix/matrix.h"
#include "edge/edge.h"

/* Predpokladana delka radky */
#define LINE_LEN 8192
#define DELIMITER ","
#define DEFAULT_ITEMS_COUNT 4
#define IS_VALID "True"




int* load_nodes(const char *file_name, int *nodes_count) {
    /* Souborovy vstup/vystup */
    FILE *fr;
    char line[LINE_LEN];
    /* pole vsech uzlu, defaultne nastaveno na "4" prvky, bude se zvetsovat*/
    int *nodes;
    /* aktualni delka pole nodes*/
    int curr_length;

    if (!file_name)
        return NULL;

    nodes = (int*)calloc(DEFAULT_ITEMS_COUNT, sizeof(int));
    if (nodes == NULL) {
        printf("Memory not allocated.\n");
        return NULL;
    }
    curr_length = DEFAULT_ITEMS_COUNT;

    /* vynulovani znaku v pameti "line" */
    memset(line, 0, LINE_LEN);

    //otevreni souboru
    fr = fopen(file_name, "r");
    if (fr == NULL) {
        printf("No Such File !! ");
        return NULL;
    }
    while (!feof(fr)) {
        fgets(line, LINE_LEN, fr);
        // pokud line obsahuje "id", automaticky se rozumi, ze jde o prvni radku, rovnou se preskoci
        if (strstr(line, "id") == NULL){
            char *token = strtok(line, DELIMITER);
            if (token != NULL) {
                // TODO dodelat osetreni konverze
                int tmp = atoi(token);

                if (tmp < curr_length){
                    nodes[tmp] = tmp;

                } else {

                    nodes = realloc(nodes, (tmp+1) * sizeof(int));
                    for (int i = curr_length; i <= tmp; i++) {
                        nodes[i] = 0;
                    }
                    curr_length = tmp +1;
                    nodes[tmp] = tmp;
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

    *nodes_count = curr_length;

    return nodes;

}


edge * load_edges(const char *file_name) {
    /* Souborovy vstup/vystup */
    FILE *fr;
    char line[LINE_LEN];

    edge *temps;

    memset(line, 0, LINE_LEN);

    //otevreni souboru
    fr = fopen(file_name, "r");
    if (fr == NULL) {
        printf("No Such File !! ");
        return NULL;
    }

    while (!feof(fr)) {
        fgets(line, LINE_LEN, fr);
        // pokud line obsahuje "id", automaticky se rozumi, ze jde o prvni radku, rovnou se preskoci
        if (strstr(line, "id,source") == NULL) {
//            printf("%s\n", line);

            edge_add(&temps, line);

            //TODO doresit valid/invalid
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


    int *nodes = NULL;
    int nodes_count;
    edge *list_edges = NULL;
    matrix *m_capacities = NULL;
    matrix *m_edges = NULL;


    nodes_count = 0;
    nodes = load_nodes("./data/plzen/pilsen_nodes.csv", &nodes_count);
//    nodes = load_nodes("./data/example/example_nodes.csv", &nodes_count);
//    for (int i = 0; i < 5001; i++)
//        printf("%d\n", nodes[i]);
    if (!nodes) {
        printf("Invalid vertex file.\n");
        return 1;
    }


    list_edges = load_edges("./data/plzen/pilsen_edges.csv");
//    list_edges = load_edges("./data/example/example_edges.csv");

    if (!list_edges) {
        printf("Invalid edges file.\n");
        return 6;
    }
    m_edges = matrix_create(nodes_count, nodes_count, 0);
    m_capacities = matrix_create(nodes_count, nodes_count, 0);

    matrix_fill_edges(m_capacities, m_edges, list_edges);
    // uvolneni pameti nodes
    free(nodes);
    // uvolneni pameti edges
    edge_free(&list_edges);

    matrix_free(&m_edges);
    matrix_free(&m_capacities);

    return 0;
}
