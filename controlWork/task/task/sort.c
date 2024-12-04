#include "binTree.h"
#include <stdlib.h>
#include <stdio.h>

void sort(int* array, int length) {
    BinTree* binTree = NULL;
    for (int i = 0; i < length; i++) {
        insert(&binTree, array[i]);
    }

    int index = 0; 
    sortByTree(binTree, array, &index);
    removebinTree(&binTree);
}