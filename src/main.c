#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Predpokladana delka radky */
#define LINE_LEN 256
#define DELIMITER ','

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
        if (strstr(line, "id") == NULL) {
            printf("%s", line);

        }
        memset(line, 0, LINE_LEN);
    }

    if (fclose(fr) == EOF)
    {
        printf("Soubor pro cteni se nepodarilo uzavrit.");
        return;
    }

}


int main() {
    printf("Hello, World!\n");

    load_nodes("./data/plzen/pilsen_nodes.csv");
    //  load_edges(argv[2]);

    return 0;
}
