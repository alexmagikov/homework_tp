#define _CRT_SECURE_NO_WARNINGS

#include "graph.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

Graph* createGraph() {
    FILE* file = fopen("file.txt", "r");
    if (file == NULL) {
        return NULL;
    }
    
    Graph* graph = malloc(sizeof(Graph));
    if (graph == NULL) {
        return NULL;
    }
    int numELements = 0;
    fscanf(file, "%d", &numELements);
    graph->numElements = numELements;
    
    graph->matrix = malloc(numELements * sizeof(int));
    if (graph->matrix == NULL) {
        return NULL;
    }
    for (int i = 0; i < numELements; i++) {
        graph->matrix[i] = calloc(numELements, sizeof(int*));
        if (graph->matrix[i] == NULL) {
            return NULL;
        }
    }

    for (int i = 0; i < numELements; i++) {
        for (int j = 0; j < numELements; j++) {
            int edge = 0;
            fscanf(file, "%d", &edge);
            graph->matrix[i][j] = edge;
        }
    }

    return graph;
}

void BFS(Graph* graph, int start) {
    int* visitedScale = (int*)calloc(graph->numElements, sizeof(int));

    int* queue = (int*)malloc(graph->numElements * sizeof(int));
    int front = 0;
    int rear = 0;

    visitedScale[start] = 1;
    queue[rear] = start;
    rear++;

    while (front < rear) {
        int current = queue[front];
        front++;
        printf("%d ", current);

        for (int i = 0; i < graph->numElements; i++) {
            if (graph->matrix[current][i] && !visitedScale[i]) {
                visitedScale[i] = 1;
                queue[rear] = i;
                rear++;
            }
        }
    }

    free(visitedScale);
    free(queue);
}


void removeGraph(Graph* graph) {
    if (graph == NULL) {
        return;
    }

    for (int i = 0; i < graph->numElements; i++) {
        free(graph->matrix[i]);
    }

    free(graph->matrix);
    free(graph);
}