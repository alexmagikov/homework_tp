#define _CRT_SECURE_NO_WARNINGS

#include "binTree.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct BinTree {
	int value;
	BinTree* leftChild;
	BinTree* rightChild;
} BinTree;

void insert(BinTree** binTree, int value) {
    if (*binTree == NULL) {
        *binTree = (BinTree*)calloc(1, sizeof(BinTree));
        if (*binTree == NULL) {
            return;
        }
        (*binTree)->value = value;
        (*binTree)->rightChild = NULL;
        (*binTree)->leftChild = NULL;
    }
    else {
        if (value >= (*binTree)->value) {
            insert(&(*binTree)->rightChild, value);
        }
        else if (value < (*binTree)->value) { 
            insert(&(*binTree)->leftChild, value);
        }
    }
}

void sortByTree(BinTree* binTree, int* array, int* index) {
	if (binTree == NULL) {
		return;
	}
	sortByTree(binTree->leftChild, array, index);
	array[(*index)] = binTree->value;
	(*index)++;
	sortByTree(binTree->rightChild, array, index);
}

void removebinTree(BinTree** binTree) {
	if (*binTree == NULL) {
		return;
	}
	removebinTree(&(*binTree)->leftChild);
	removebinTree(&(*binTree)->rightChild);
	free(*binTree);
	*binTree = NULL;
}