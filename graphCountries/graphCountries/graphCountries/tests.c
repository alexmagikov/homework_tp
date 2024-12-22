#include "tests.h"
#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

bool testForNormalValue() {
    Graph* graph = distributeForCountries("test.txt");
    List** listCountries = getGraphCountries(graph);
    int firstCountry[3] = { 0, 2, 1 };
    int secondCountry[3] = { 3, 4, 5 };
    
    Position firstPosition = first(listCountries[0]);
    firstPosition = next(firstPosition);
    for (int i = 0; i < getLength(listCountries[0]); i++) {
        if (getValue(listCountries[0], firstPosition) != firstCountry[i]) {
            removeGraph(graph);
            return false;
        }
        firstPosition = next(firstPosition);
    }

    Position secondPosition = first(listCountries[3]);
    secondPosition = next(secondPosition);
    for (int i = 0; i < getLength(listCountries[3]); i++) {
        if (getValue(listCountries[3], secondPosition) != secondCountry[i]) {
            removeGraph(graph);
            return false;
        }
        secondPosition = next(secondPosition);
    }
    
    removeGraph(graph);
    return true;
}

bool areTestsCompleted() {
    bool tests[1] = { testForNormalValue() };
    for (int i = 0; i < 1; i++) {
        if (!tests[i]) {
            return false;
        }
    }
}