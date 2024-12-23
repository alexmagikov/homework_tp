#define _CRT_SECURE_NO_WARNINGS

#include "hashTable.h"
#include <stdio.h>
#include "tests.h"
#include <stdlib.h>

int main() {


    HashTable* hashTable = createHashTable(100);
    char bufferSymbol = '\0';
    char* bufferWord = NULL;
    int lengthOfWord = 0;
    FILE* file = fopen("text.txt", "r");
    if (file == NULL) {
        return -1;
    }
    while ((bufferSymbol = fgetc(file))) {
        if (bufferSymbol == '\n' || bufferSymbol == ' ' || bufferSymbol == EOF) {
            bufferWord[lengthOfWord] = '\0';
            hashTable = insert(hashTable, bufferWord);
            bufferWord = NULL;
            lengthOfWord = 0;
            if (bufferSymbol == EOF) {
                break;
            }
            continue;
        }
        bufferWord = realloc(bufferWord, (lengthOfWord + 2) * sizeof(char));
        if (bufferWord == NULL) {
            printf("mem error");
            return -1;
        }
        bufferWord[lengthOfWord] = bufferSymbol;
        lengthOfWord++;
    }
    fclose(file);
    printHashTable(hashTable);
    printf("fill Factor - %.2f\n", getFillFactor(hashTable));
    printf("Avarage length of list - %d\n", getAvarageLengthOfListsOfBuckets(hashTable));
    printf("Max length of list - %d\n", getMaxLengthOfList(hashTable));
    return 0;
}