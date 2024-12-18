#pragma once

typedef struct Graph {
    int** matrix;
    int numElements;
} Graph;

// create Graph with adjacency matrix by file
Graph* createGraph();

// print graph by bfs
void BFS(Graph* graph, int start);

// free graph memory 
void removeGraph(Graph* graph);