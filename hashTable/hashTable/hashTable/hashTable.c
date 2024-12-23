#define _CRT_SECURE_NO_WARNINGS

#include "hashTable.h"
#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct HashItem {
    int hash;
    List* entries;
} HashItem;

typedef struct HashTable {
    HashItem** buckets;
    int size;
    int numOfElements;
} HashTable;

int hash(char* value, int size) {
    int result = 0;
    for (int i = 0; value[i] != '\0'; i++) {
        result = (result + value[i]) % size;
    }
    return result;
}

HashTable* createHashTable(int size) {
    HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
    if (hashTable == NULL) {
        return NULL;
    }
    hashTable->buckets = (HashItem**)malloc(size * sizeof(HashItem*));
    if (hashTable->buckets == NULL) {
        free(hashTable);
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        hashTable->buckets[i] = NULL;
    }
    hashTable->size = size;
    hashTable->numOfElements = 0;
    return hashTable;
}

HashItem* createHashItem(int hashValue, char* value) {
    HashItem* hashItem = (HashItem*)malloc(sizeof(HashItem));
    if (hashItem == NULL) {
        return NULL;
    }
    List* entries = createList();
    Position position = first(entries);
    Value hashItemValue = {.entry = malloc(sizeof(char) * (1 + strlen(value))),.count = 1};
    if (hashItemValue.entry == NULL) {
        free(hashItem);
        return NULL;
    }
    strcpy(hashItemValue.entry, value);
    add(entries, position, hashItemValue);
    hashItem->entries = entries;
    hashItem->hash = hashValue;
    return hashItem;
}

HashTable* addToHashItem(HashTable* hashTable, int index, char* value) {
    HashItem* hashItem = hashTable->buckets[index];
    List* list = hashItem->entries;
    Position position = first(list);
    while (!isLast(list, position)) {
        position = next(position);
        if (!strcmp(getValue(list, position).entry, value)) {
            Value newValue = { .count = getValue(list, position).count + 1, .entry = getValue(list, position).entry };
            setValue(list, position, newValue);
            hashItem->entries = list;
            return hashTable;
        }
    }
    Value newValue = { .count = 1, .entry = malloc((strlen(value) + 1) * sizeof(char)) };
    strcpy(newValue.entry, value);
    add(list, position, newValue);
    hashTable->numOfElements++;
    hashItem->entries = list;
    return hashTable;
}

HashTable* updateHashTable(HashTable* hashTable) {
    HashTable* newHashTable = createHashTable(hashTable->size * 2);
    for (int i = 0; i < hashTable->size; i++) {
        if (hashTable->buckets[i] != NULL) {
            List* list = hashTable->buckets[i]->entries;
            Position position = first(list);
            while (!isLast(list, position)) {
                position = next(position);
                for (int j = 0; j < getValue(list, position).count; j++) {
                    newHashTable = insert(newHashTable, getValue(list, position).entry);
                }
            }
        }
    }
    return newHashTable;
}

HashTable* insert(HashTable* hashTable, char* value) {
    int index = hash(value, hashTable->size);
    if (getFillFactor(hashTable) > 1) {
        hashTable = updateHashTable(hashTable);
    }
    if (hashTable->buckets[index] == NULL) {
        hashTable->buckets[index] = createHashItem(index, value);
        hashTable->numOfElements++;
    }
    else {
        return addToHashItem(hashTable, index, value);
    }
    return hashTable;
}

int getCount(HashTable* hashTable, char* value) {
    int index = hash(value, hashTable->size);
    if (hashTable->buckets[index] == NULL) {
        return -1;
    }
    List* list = hashTable->buckets[index]->entries;
    Position position = first(list);
    while (!isLast(list, position)) {
        position = next(position);
        if (!strcmp(getValue(list, position).entry, value)) {
            return getValue(list, position).count;
        }
    }
}

void printHashTable(HashTable* hashTable) {
    for (int i = 0; i < hashTable->size; i++) {
        if (hashTable->buckets[i] != NULL) {
            List* list = hashTable->buckets[i]->entries;
            Position position = first(list);
            while (!isLast(list, position)) {
                position = next(position);
                printf("%d - %s - %d\n", hashTable->buckets[i]->hash, getValue(list, position).entry, getValue(list, position).count);
            }
        }
    }
}

HashTable* removeFromHashTable(HashTable* hashTable, char* value) {
    int index = hash(value, hashTable->size);
    if (hashTable->buckets[index] == NULL) {
        printf("error: no value in hashTable");
        return NULL;
    }
    List* list = hashTable->buckets[index]->entries;
    Position position = first(list);
    if (isLast(list, next(position))) {
        removeFromList(list, position);
        free(hashTable->buckets[index]->entries);
        free(hashTable->buckets[index]);
        hashTable->buckets[index] = NULL;
        return hashTable;
    }
    while (!isLast(list, position)) {
        if (!strcmp(getValue(list, next(position)).entry, value)) {
            removeFromList(list, position);
        }
        position = next(position);
    }
    return hashTable;
}

void removeHashTable(HashTable* hashTable) {
    for (int i = 0; i < hashTable->size; i++) {
        if (hashTable->buckets[i] != NULL) {
            List* list = hashTable->buckets[i]->entries;
            Position position = first(list);
            while (!isLast(list, position)) {
                removeFromList(list, position);
            }
        }
    }
    free(hashTable);
}

float getFillFactor(HashTable* hashTable) {
    float result = (float)hashTable->numOfElements / (float)hashTable->size;
    return result;
}

int getAvarageLengthOfListsOfBuckets(HashTable* hashTable) {
    int sumOfLength = 0;
    for (int i = 0; i < hashTable->size; i++) {
        if (hashTable->buckets[i] != NULL) {
            List* list = hashTable->buckets[i]->entries;
            Position position = first(list);
            while (!isLast(list, position)) {
                position = next(position);
                sumOfLength++;
            }
        }
    }
    return sumOfLength / hashTable->numOfElements;
}

int getMaxLengthOfList(HashTable* hashTable) {
    int max = 0;
    for (int i = 0; i < hashTable->size; i++) {
        if (hashTable->buckets[i] != NULL) {
            List* list = hashTable->buckets[i]->entries;
            if (getLength(list) > max) {
                max = getLength(list);
            }
        }
    }
    return max;
}



