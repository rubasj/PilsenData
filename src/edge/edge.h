//
// Created by janru on 21.11.2021.
//

#ifndef PILSENDATA_EDGE_H
#define PILSENDATA_EDGE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct edge_{
    int id;
    int source;  /* pocatecni vrchol */
    int target;
    int capacity;
    char *description;
    struct edge_ *next; /* spojovaci prvek seznamu */
} edge;

/**
 * Pridani dalsi hrany
 * @param list  seznam, do ktereho se prida nova hrana.
 * @param line  radka ze souboru pro generovani nove hrany
 */
int *edge_add(edge **list, char *line);

/**
 * Uvolneni seznamu vrcholu
 * @param head seznam vrcholu
 */
void edge_free(edge **head);


#endif //PILSENDATA_EDGE_H
