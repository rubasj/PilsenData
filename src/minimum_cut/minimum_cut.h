//
// Created by janru on 02.12.2021.
//

#ifndef PILSENDATA_MINIMUM_CUT_H
#define PILSENDATA_MINIMUM_CUT_H

#include "../matrix/matrix.h"

int bfs(matrix *rGraph, const int s, const int t, int parent[]);
void minCut(matrix *graph, int s, int t);
#endif //PILSENDATA_MINIMUM_CUT_H
