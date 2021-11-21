#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

/* Predpokladana delka radky */
#define LINE_LEN 256
#define DELIMITER ","
#define DEFAULT_ITEMS_COUNT 4




void load_nodes(const char *file_name) {
    /* Souborovy vstup/vystup */
    FILE *fr;
    char line[LINE_LEN];
    /* pole vsech uzlu, defaultne nastaveno na "4" prvky, bude se zvetsovat*/
    int *nodes;
    /* aktualni delka pole nodes*/
    int curr_length;

    nodes = (int*)calloc(DEFAULT_ITEMS_COUNT, sizeof(int));
    if (nodes == NULL) {
        printf("Memory not allocated.\n");
        return;
    }
    curr_length = DEFAULT_ITEMS_COUNT;

    /* vynulovani znaku v pameti "line" */
    memset(line, 0, LINE_LEN);

    //otevreni souboru
    fr = fopen(file_name, "r");
    if (fr == NULL) {
        printf("No Such File !! ");
        return;
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
                    //printf("%d\n",nodes[tmp]);
                } else {
                    curr_length = tmp +1;
                    nodes = realloc(nodes, (tmp+1) * sizeof(int));
                    nodes[tmp] = tmp;
                }
            }

        }
        memset(line, 0, LINE_LEN);
    }

    if (fclose(fr) == EOF)
    {
        printf("Soubor pro cteni se nepodarilo uzavrit.");
        return;
    }

    int i;

    for (i = 0; i < curr_length; i++) {
        printf("%d\n", nodes[i]);
    }

}


void load_edges(const char *file_name) {
    /* Souborovy vstup/vystup */
    FILE *fr;
    char line[LINE_LEN];
    int nodes_count = 0;
    memset(line, 0, LINE_LEN);

    //otevreni souboru
    fr = fopen(file_name, "r");
    if (fr == NULL) {
        printf("No Such File !! ");
        return;
    }


    while (!feof(fr)) {
        fgets(line, LINE_LEN, fr);
        // pokud line obsahuje "id", automaticky se rozumi, ze jde o prvni radku, rovnou se preskoci
        if (strstr(line, "id") == NULL != 0) {

//            printf("%s\n", line);
            int tmp = 0;
            char *token = strtok(line, DELIMITER);
            // loop through the string to extract all other tokens
            while (token != NULL) {
                tmp++;
                printf("%s ", token);

                token = strtok(NULL, DELIMITER);

                if (tmp == 3)
                    break;
            }
            printf("\n");

        }
        memset(line, 0, LINE_LEN);
    }

    if (fclose(fr) == EOF)
    {
        printf("Soubor pro cteni se nepodarilo uzavrit.");
        return;
    }
}


int main(int argc, char *argv[]) {
    printf("Hello, World!\n");

    load_nodes("./data/plzen/pilsen_nodes.csv");
//    load_edges("./data/plzen/pilsen_edges.csv");

    return 0;
}
