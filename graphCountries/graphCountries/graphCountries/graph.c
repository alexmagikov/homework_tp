#define _CRT_SECURE_NO_WARNINGS

#include "graph.h"
#include "list.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Graph {
    List** countries;
    int numCities;
} Graph;

Graph* createGraph(int numCities) {
    Graph* graph = malloc(sizeof(Graph));
    if (graph == NULL) {
        return NULL;
    }
    graph->numCities = numCities;
    graph->countries = malloc(numCities * sizeof(List*));
    if (graph->countries == NULL) {
        return NULL;
    }
    for (int i = 0; i < numCities; i++) {
        graph->countries[i] = NULL;
    }
    return graph;
}

Graph* addNote(Graph* graph, int country, int numCities, int** matrix, bool** distributeScale) {
    int nearestLength = 1000;
    int nearestCity = -1;

    if (graph->countries[country] == NULL) {
        graph->countries[country] = createList();
        Position position = first(graph->countries[country]);
        add(graph->countries[country], position, country);
        (*distributeScale)[country] = true;
        return graph;
    }
    
    Position position = first(graph->countries[country]);
    for (int i = 0; i < getLength(graph->countries[country]); i++) {
        position = next(position);
        int cityOfCountry = getValue(graph->countries[country], position);
        for (int j = 0; j < numCities; j++) {
            if (matrix[cityOfCountry][j] != 0 && !(*distributeScale)[j] && j != country) {
                if (matrix[cityOfCountry][j] < nearestLength) {
                    nearestLength = matrix[cityOfCountry][j];
                    nearestCity = j;
                }
            }
        }
    }
    (*distributeScale)[nearestCity] = true;
    add(graph->countries[country], position, nearestCity);
    return graph;
}

void printGraph(Graph* graph) {
    for (int country = 0; country < graph->numCities; country++) {
        if (graph->countries[country] != NULL) {
            Position position = first(graph->countries[country]);
            position = next(position); 
            
            int capital = getValue(graph->countries[country], position);
            printf("Capital - %d Cities: ", capital);

            for (int j = 1; j < getLength(graph->countries[country]); j++) {
                position = next(position);
                int city = getValue(graph->countries[country], position);
                printf("%d ", city);
            }
            printf("\n");
        }
    }
}

List** getGraphCountries(Graph* graph) {
    return graph->countries;
}

int getGraphNumCities(Graph* graph) {
    return graph->numCities;
}

bool allDistribute(int numCities, bool* distributeScale) {
    for (int i = 0; i < numCities; i++) {
        if (!distributeScale[i]) {
            return false;
        }
    }
    return true;
}

void removeGraph(Graph* graph) {
    for (int i = 0; i < graph->numCities; i++) {
        if (graph->countries[i] != NULL) {
            freeListElements(graph->countries[i]);
        }
    }
    free(graph->countries);
    free(graph);
}

Graph* distributeForCountries(char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("open fail");
        return NULL;
    }
    int numCities = 0;
    fscanf(file, "%d", &numCities);
    int numRoads = 0;
    fscanf(file, "%d", &numRoads);

    int** matrix = malloc(numCities * sizeof(int*));
    if (matrix == NULL) {
        printf("mem fail");
        return NULL;
    }
    for (int i = 0; i < numCities; i++) {
        matrix[i] = calloc(numCities, sizeof(int));
        if (matrix[i] == NULL) {
            printf("mem fail");
            return NULL;
        }
    }

    for (int i = 0; i < numRoads; i++) {
        int from = 0;
        int to = 0;
        int length = 0;
        fscanf(file, "%d %d %d", &from, &to, &length);
        matrix[from][to] = length;
        matrix[to][from] = length;
    }

    int numCapitals = 0;
    fscanf(file, "%d", &numCapitals);
    Graph* countries = createGraph(numCities);
    bool* distributeScale = calloc(numCities, sizeof(bool));

    int* capitals = malloc(numCapitals * sizeof(int));

    for (int i = 0; i < numCapitals; i++) {
        int capital = -1;
        fscanf(file, "%d", &capital);
        countries = addNote(countries, capital, numCities, matrix, &distributeScale);
        capitals[i] = capital;
    }

    int index = 0;

    while (!allDistribute(numCities, distributeScale)) {
        addNote(countries, capitals[index], numCities, matrix, &distributeScale);
        index++;
        if (index >= numCapitals) {
            index = 0;
        }
    }
    fclose(file);
    for (int i = 0; i < numCities; i++) {
       free(matrix[i]);
    }
    free(matrix);
    return countries;
}