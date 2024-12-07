#define _CRT_SECURE_NO_WARNINGS

#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>

int searchMostFreaqmentElement(int array[], int numOfElements) {
    int mostFreaqment = -1;
    int countOfFreaqmentMax = 0;
    int countOfFreaqment = 0;
    for (int i = 0; i < numOfElements - 1; i++) {
        countOfFreaqment++;
        if (array[i] != array[i + 1]) {
            if (countOfFreaqmentMax < countOfFreaqment) {
                countOfFreaqmentMax = countOfFreaqment;
                mostFreaqment = array[i];
            }
            countOfFreaqment = 0;
        }
    }
    countOfFreaqment++;
    if (countOfFreaqment > countOfFreaqmentMax) {
        mostFreaqment = array[numOfElements - 1];
    }
    return mostFreaqment;
}

typedef struct {
    int* array;
    int numOfElements;
} Array;

Array createArray() {
    Array result;
    FILE* file = fopen("data.txt", "r");
    int* array = NULL;
    char buffer[10];
    int index = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        array = (int*)realloc(array, (index + 1) * sizeof(int));
        array[index] = atoi(buffer);
        index++;
    }

    fclose(file);
    result.array = array;
    result.numOfElements = index;
    return result;
}

void main(void) {
    Array array = createArray();
    printf("array int txt ");
    for (int i = 0; i < array.numOfElements; i++) {
        printf("%d ", array.array[i]);
    }
    qSort(array.array, 0, array.numOfElements - 1);
    printf("\nMost freaqment element is %d ", searchMostFreaqmentElement(array.array, array.numOfElements));
}

