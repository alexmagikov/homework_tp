#include "binTree.h"
#include "sort.h"
#include <stdlib.h>

bool testForSortByTreeForNormalValue() {
    BinTree* binTree = NULL;
    insert(&binTree, 6);
    insert(&binTree, 3);
    insert(&binTree, 1);
    insert(&binTree, 4);
    insert(&binTree, 7);
    insert(&binTree, 8);
    int* array = malloc(6 * sizeof(int));
    int index = 0;
    sortByTree(binTree, array, &index);
    for (int i = 0; i < 5; i++) {
        if (array[i] > array[i + 1]) {
            return false;
        }
    }
    return true;
}

bool testForSortByTreeForEqualValue() {
    BinTree* binTree = NULL;
    insert(&binTree, 6);
    insert(&binTree, 6);
    insert(&binTree, 6);
    insert(&binTree, 6);
    insert(&binTree, 6);
    insert(&binTree, 6);
    int* array = malloc(6 * sizeof(int));
    int index = 0;
    sortByTree(binTree, array, &index);
    for (int i = 0; i < 5; i++) {
        if (array[i] > array[i + 1]) {
            return false;
        }
    }
    return true;
}

bool testForSortByTreeForDoublicateslValue() {
    BinTree* binTree = NULL;
    insert(&binTree, 6);
    insert(&binTree, 2);
    insert(&binTree, 7);
    insert(&binTree, 4);
    insert(&binTree, 6);
    insert(&binTree, 10);
    int* array = malloc(6 * sizeof(int));
    int index = 0;
    sortByTree(binTree, array, &index);
    for (int i = 0; i < 5; i++) {
        if (array[i] > array[i + 1]) {
            return false;
        }
    }
    return true;
}

bool testForSortForEqual() {
    int array[5] = { 1,1,1,1,1 };
    sort(array, 5);
    for (int i = 0; i < 4; i++) {
        if (array[i] > array[i + 1]) {
            return false;
        }
    }
    return true;
}

bool testForSortForDoublicates() {
    int array[5] = { 6,1,10,2,6 };
    sort(array, 5);
    for (int i = 0; i < 4; i++) {
        if (array[i] > array[i + 1]) {
            return false;
        }
    }
    return true;
}

bool isCompletedTests() {
    bool* tests[5] = {
        testForSortByTreeForNormalValue(),
        testForSortByTreeForEqualValue(),
        testForSortByTreeForDoublicateslValue(),
        testForSortForEqual(),
        testForSortForDoublicates(),
    };
    for (int i = 0; i < 5; i++) {
        if (!tests[i]) {
            printf("test %d failed", i);
            return false;
        }
    }
    return true;
}