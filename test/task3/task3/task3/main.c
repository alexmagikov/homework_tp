#include "graph.h"

int main() {
    Graph* graph = createGraph();
    BFS(graph, 1);
    removeGraph(graph);
    return 0;
}