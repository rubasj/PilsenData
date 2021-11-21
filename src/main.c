#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

/* Predpokladana delka radky */
#define LINE_LEN 256
#define DELIMITER ","

void load_nodes(char *file_name) {
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
        if (strstr(line, "id") == NULL){

            char *token = strtok(line, DELIMITER);
            if (token != NULL) {
                printf("%d\n", atoi(token));
            }

        }
        memset(line, 0, LINE_LEN);
    }

    if (fclose(fr) == EOF)
    {
        printf("Soubor pro cteni se nepodarilo uzavrit.");
        return;
    }

}


void load_edges(char *file_name) {
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

//    load_nodes("./data/plzen/pilsen_nodes.csv");
    load_edges("./data/plzen/pilsen_edges.csv");

    return 0;
}
