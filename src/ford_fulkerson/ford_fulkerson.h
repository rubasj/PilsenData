//
// Created by janru on 30.11.2021.
//

#ifndef PILSENDATA_FORD_FULKERSON_H
#define PILSENDATA_FORD_FULKERSON_H
#include <string.h>
#include <limits.h>
#include "../matrix/matrix.h"

int bfs(matrix *rGraph, const int s, const int t, int parent[]);

int ford_fulkerson(matrix *graph, const int s, const int t);

#endif //PILSENDATA_FORD_FULKERSON_H
