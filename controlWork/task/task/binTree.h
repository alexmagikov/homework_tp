#pragma once
#include <stdbool.h>

typedef struct BinTree BinTree;

// insert into binTree. if binTree NULL then initialize them
void insert(BinTree** dictionary, int value);

// sort array by binTree
void sortByTree(BinTree* binTree, int* array, int* index);

// free binTree
void removebinTree(BinTree** dictionary);