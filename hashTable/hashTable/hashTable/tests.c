#include "tests.h"
#include "hashTable.h"
#include <stdio.h>

#include <stdlib.h>

#define numOfTests 8
#define EPSILON 1e-6

bool testForCreateHashTable() {
    HashTable* hashTable = createHashTable(100);
    return hashTable != NULL;
}

bool testForCreateHashItem() {
    int index = hash("test", 100);
    HashItem* hashItem = createHashItem(index, "test");
    return hashItem != NULL;
}

bool testForInsertForSingleValue() {
    HashTable* hashTable = createHashTable(100);
    hashTable = insert(hashTable, "test");
    return getCount(hashTable, "test") == 1;
}

bool testForInsertForDoubleValue() {
    HashTable* hashTable = createHashTable(100);
    hashTable = insert(hashTable, "test");
    hashTable = insert(hashTable, "test");
    return getCount(hashTable, "test") == 2;
}

bool testForRemoveValue() {
    HashTable* hashTable = createHashTable(100);
    hashTable = insert(hashTable, "test");
    hashTable = removeFromHashTable(hashTable, "test");
    return getCount(hashTable, "test") == -1;
}

bool testForFillFactor() {
    HashTable* hashTable = createHashTable(100);
    hashTable = insert(hashTable, "test");
    float expected = 1.0f / 100.0f; 
    return abs(getFillFactor(hashTable) - expected) < EPSILON;
}

bool testForAvarageLengthOfList() {
    HashTable* hashTable = createHashTable(100);
    hashTable = insert(hashTable, "test");
    return  getAvarageLengthOfListsOfBuckets(hashTable) == 1;
}

bool testForGetMaxLengthOfList() {
    HashTable* hashTable = createHashTable(100);
    hashTable = insert(hashTable, "test");
    return  getMaxLengthOfList(hashTable) == 1;
}

bool isCompleted() {
    bool* tests[numOfTests] = {
        testForCreateHashTable(),
        testForCreateHashItem(),
        testForInsertForSingleValue(),
        testForInsertForDoubleValue(),
        testForRemoveValue(),
        testForFillFactor(),
        testForAvarageLengthOfList(),
        testForGetMaxLengthOfList(),
    };
    for (int i = 0; i < numOfTests; i++) {
        if (!tests[i]) {
            printf("test %d failed", i);
            return false;
        }
    }
    return true;
}