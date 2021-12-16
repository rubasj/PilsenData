#include "algorithm.h"



/* Returns true if there is a path from source 's' to sink 't' in
residual graph. Also fills parent[] to store the path */
int bfs(matrix *rGraph, const int s, const int t, int *parent)
{
    int visited[rGraph->cols], u;
    size_t i;
    queue *q;
    if (!rGraph || !parent) {
        printf("BFS: Missing function argument.");
        return 0;
    }
    /* vytvoreni pole prozkoumanych uzlu */

    memset(visited, 0, sizeof(visited));

    /* Vytvoreni fronty, vlozeni zdrojoveho uzlu a oznaceni zdroje jako proykoumane */


    q = createQueue(4);
    push(q, s);
    visited[s] = 1;
    parent[s] = -1;

    while (!isEmpty(q))
    {
        u = front(q);
        pop(q);

        for (i = 0; i < rGraph->cols; i++)
        {
            if (visited[i] == 0 && matrix_get_item(rGraph, u, i) > 0)
            {
                push(q, i);
                parent[i] = u;
                visited[i] = 1;
            }
        }
    }

    free_queue(q);
    /* pokud dosahne stoku v BFS ze zdroje oznaci jako 1, jinak 0 */
    return visited[t];
}

/* A DFS based function to find all reachable vertices from s. The function
   marks visited[i] as true if i is reachable from s. The initial values in
   visited[] must be false. We can also use BFS to find reachable vertices */
void dfs(matrix *rGraph, int s, int *visited)
{
    size_t i;
    if (!rGraph || !visited) {
        printf("DFS: Missing function argument.");
        return;
    }
    visited[s] = 1;
    for (i = 0; i < rGraph->cols; i++)
        if (matrix_get_item(rGraph, s, i) && !visited[i])
            dfs(rGraph, i, visited);
}

int min(int x, int y) {
    return x < y ? x : y;
}


int ford_fulkerson(const matrix *graph, const matrix *m_edges,int s, int t, int out_active, vector_t *min_cut) {
    matrix *rGraph;
    int parent[graph->cols], max_flow, path_flow, visited[rGraph->cols], tmp, edge_id, u, v;
    size_t i, j;


    if (!graph || s == -1 || t == -1) {
        printf("Ford_fulkerson: Missing argument.");
        return 0;
    }


    /* Create a residual graph and fill the residual graph with
    // given capacities in the original graph as residual capacities
    // in residual graph */

    rGraph = matrix_duplicate(graph);

    max_flow = 0;

    while (bfs(rGraph, s, t, parent)) {

        path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, matrix_get_item(rGraph, u, v));
        }

        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            matrix_set(rGraph, u, v, (matrix_get_item(rGraph, u, v) - path_flow));
            matrix_set(rGraph, v, u, (matrix_get_item(rGraph, v, u) + path_flow));
        }

        max_flow += path_flow; /* There is no flow initially*/
    }
    printf("\n");



    printf("Max network flow is |x| = %d.\n", max_flow);


    if (out_active == 1) {
        /* Flow is maximum now, find vertices reachable from s */
        memset(visited, 0, sizeof(visited));
        dfs(rGraph, s, visited);

        /* Print all edges that are from a reachable vertex to
        // non-reachable vertex in the original graph */
        for (i = 0; i < rGraph->cols; i++) {
            for (j = 0; j < rGraph->cols; j++) {

                if (visited[i] && !visited[j] && matrix_get_item(graph, i, j)) {
                    edge_id = matrix_get_item(m_edges, i, j);
                    tmp = vector_push_back(min_cut, &edge_id);

                    if (tmp == -1) {
                        printf("Ford_Fulekrson: Nepodarilo se vlozit id hrany do vektoru.\n");
                        return -1;
                    }
                }
            }
        }
    }



    matrix_free(&rGraph);

    return max_flow;
}

