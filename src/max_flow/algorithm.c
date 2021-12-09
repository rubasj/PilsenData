//
// Created by janru on 02.12.2021.
//

#include "algorithm.h"



/* Returns true if there is a path from source 's' to sink 't' in
residual graph. Also fills parent[] to store the path */
int bfs(matrix *rGraph, const int s, const int t, int *parent)
{

    if (!rGraph, !parent) {
        printf("BFS: Missing function argument.");
        return 0;
    }
    // Create a visited array and mark all vertices as not visited
    int visited[rGraph->cols];
    memset(visited, 0, sizeof(visited));

    // Create a queue, push source vertex and mark source vertex
    // as visited

    queue *q;
    q = createQueue(4);
    push(q, s);
//    q.push(s);
    visited[s] = 1;
    parent[s] = -1;

    // Standard BFS Loop
    while (!isEmpty(q))
    {
        int u = front(q);
        pop(q);

        for (int v=0; v < rGraph->cols; v++)
        {
            if (visited[v]== 0 && matrix_get_item(rGraph, u, v) > 0)
            {
                push(q, v);
                parent[v] = u;
                visited[v] = 1;
            }
        }
    }

    free_queue(q);
    // If we reached sink in BFS starting from source, then return
    // 1, else 0
    return visited[t];
}

// A DFS based function to find all reachable vertices from s. The function
// marks visited[i] as true if i is reachable from s. The initial values in
// visited[] must be false. We can also use BFS to find reachable vertices
void dfs(matrix *rGraph, int s, int *visited)
{
    if (!rGraph, !visited) {
        printf("DFS: Missing function argument.");
        return;
    }
    visited[s] = 1;
    for (int i = 0; i < rGraph->cols; i++)
        if (matrix_get_item(rGraph, s, i) && !visited[i])
            dfs(rGraph, i, visited);
}

// Prints the minimum s-t cut
void ford_fulkerson(const matrix *graph, int s, int t) {

    if (!graph) {
        printf("Ford_fulkerson: Missing argument.");
        return;
    }
    int u, v;

    // Create a residual graph and fill the residual graph with
    // given capacities in the original graph as residual capacities
    // in residual graph
    matrix *rGraph;
    rGraph = matrix_duplicate(graph);
    matrix_print(rGraph);

    int parent[rGraph->cols]; // This array is filled by BFS and to store path
    int max_flow = 0; // There is no flow initially
    // Augment the flow while there is a path from source to sink
    while (bfs(rGraph, s, t, parent)) {
        // Find minimum residual capacity of the edhes along the
        // path filled by BFS. Or we can say find the maximum flow
        // through the path found.
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, matrix_get_item(rGraph, u, v));
        }

        // update residual capacities of the edges and reverse edges
        // along the path
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            matrix_set(rGraph, u, v, (matrix_get_item(rGraph, u, v) - path_flow));
            matrix_set(rGraph, v, u, (matrix_get_item(rGraph, v, u) + path_flow));
        }

        max_flow += path_flow; // There is no flow initially
    }
    printf("\n");

    matrix_print(graph);

    printf("Max network flow is |x| = %d.\n", max_flow);

    // Flow is maximum now, find vertices reachable from s
    int visited[rGraph->cols];
    memset(visited, 0, sizeof(visited));
    dfs(rGraph, s, visited);

    // Print all edges that are from a reachable vertex to
    // non-reachable vertex in the original graph
    for (int i = 0; i < rGraph->cols; i++) {
        for (int j = 0; j < rGraph->cols; j++) {

            if (visited[i] && !visited[j] && matrix_get_item(graph, i, j)) {

                printf("%d - %d\n", i, j);
            }
        }
    }

    matrix_free(&rGraph);
}

