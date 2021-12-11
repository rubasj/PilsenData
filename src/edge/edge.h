//
// Created by janru on 21.11.2021.
//

#ifndef PILSENDATA_EDGE_H
#define PILSENDATA_EDGE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../vector/vector.h"

typedef struct edge_{
    int id;
    int source;  /* pocatecni vrchol */
    int target;
    int capacity;
    char description[8192];
} edge;

/**
 * Pridani dalsi hrany
 * @param line  radka ze souboru pro generovani nove hrany
 */
edge *edge_create(char *line);

/**
 * Uvolneni seznamu vrcholu
 * @param head seznam vrcholu
 */
void edge_destroy(edge **poor);

edge *find_edge_by_id(const vector_t *vec, size_t id);

#endif //PILSENDATA_EDGE_H
