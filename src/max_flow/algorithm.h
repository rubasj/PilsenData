//
// Created by janru on 02.12.2021.
//

#ifndef PILSENDATA_ALGORITHM_H
#define PILSENDATA_ALGORITHM_H

#include <limits.h>
#include <string.h>
#include <minmax.h>
#include "../matrix/matrix.h"
#include "../queue/queue.h"


int bfs(matrix *rGraph, const int s, const int t, int *parent);
void ford_fulkerson(const matrix *graph, const matrix *m_edges,int s, int t, int out_active);
#endif //PILSENDATA_ALGORITHM_H
