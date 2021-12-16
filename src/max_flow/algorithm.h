

#ifndef PILSENDATA_ALGORITHM_H
#define PILSENDATA_ALGORITHM_H

#include <limits.h>
#include <string.h>
#include "../matrix/matrix.h"
#include "../queue/queue.h"

int min(int x, int y);
int bfs(matrix *rGraph, const int s, const int t, int *parent);
int ford_fulkerson(const matrix *graph, const matrix *m_edges, int s, int t, int out_active, vector_t *min_cut);
#endif
