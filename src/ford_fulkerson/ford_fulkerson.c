//
// Created by janru on 30.11.2021.
//

#include "ford_fulkerson.h"


//TODO - bez QUEUE to nebude fungovat
int bfs(matrix *rGraph, const int s, const int t, int parent[]){

// Create a visited array and mark all vertices as not
    // visited
    int visited[rGraph->cols];
    memset(visited, 0, sizeof(visited));

    // Create a queue, enqueue source vertex and mark source
    // vertex as visited
    queue<int> q;
    q.push(s);
    visited[s] = 1;
    parent[s] = -1;

    // Standard BFS Loop
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < rGraph->cols; v++) {
            if (visited[v] == 0 && rGraph[u][v] > 0) {
                // If we find a connection to the sink node,
                // then there is no point in BFS anymore We
                // just have to set its parent and can return
                // true
                if (v == t) {
                    parent[v] = u;
                    return 1;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = 1;
            }
        }
    }

    // We didn't reach sink in BFS starting from source, so
    // return false
    return 0;
}

int ford_fulkerson(matrix *graph, int s, int t){
    int u, v;

    // Create a residual graph and fill the residual graph
    // with given capacities in the original graph as
    // residual capacities in residual graph
    matrix *rGraph; // Residual graph where rGraph[i][j]
    // indicates residual capacity of edge
    // from i to j (if there is an edge. If
    // rGraph[i][j] is 0, then there is not)
    rGraph = matrix_create(graph->cols, graph->rows, 0);

    memcpy(rGraph, graph, sizeof(matrix));

    int parent[rGraph->cols]; // This array is filled by BFS and to
    // store path

    int max_flow = 0; // There is no flow initially

    // Augment the flow while there is path from source to
    // sink
    while (bfs(rGraph, s, t, parent)) {
        // Find minimum residual capacity of the edges along
        // the path filled by BFS. Or we can say find the
        // maximum flow through the path found.
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        // update residual capacities of the edges and
        // reverse edges along the path
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        // Add path flow to overall flow
        max_flow += path_flow;
    }

    matrix_free(&rGraph);

    // Return the overall flow
    return max_flow;
}