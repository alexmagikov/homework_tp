#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "tests.h"

int main() {
    if (!areTestsCompleted()) {
        return -1;
    }
    Graph* graph = distributeForCountries("file.txt");
    printGraph(graph);
    removeGraph(graph);
    return 0;
}