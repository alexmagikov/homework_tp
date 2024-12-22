#pragma once
#include <stdbool.h>
#include "list.h"

typedef struct Graph Graph;

// add nearest note to country note 
Graph* addNote(Graph* graph, int country, int numCities, int** matrix, bool** distributeScale);

// initialize graph
Graph* createGraph(int numCities);

// return true if all cities are distributed
bool allDistribute(int numCities, bool* distributeScale);

// print each capital and her cities 
void printGraph(Graph* graph);

// free graph 
void removeGraph(Graph* graph);

// distribute cities in file for countries
Graph* distributeForCountries(char* fileName);

// return array of countries
List** getGraphCountries(Graph* graph);

// return num of cities of graph
int getGraphNumCities(Graph* graph);

