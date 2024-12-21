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

typedef struct Array {
    int* array;
    int numOfElements;
} Array;

Array createArrayByDataFile() {
    Array result;
    FILE* file = fopen("data.txt", "r");
    if (file == NULL) {
        result.array = NULL;
        result.numOfElements = 0;
        return result;
    }
    result.array = (int*)malloc(13 * sizeof(int));
    if (result.array == NULL) {
        fclose(file);
        result.numOfElements = 0;
        return result;
    }

    int index = 0;
    while (index < 13 && fscanf(file, "%d", &result.array[index]) == 1) {
        index++;
    }

    fclose(file);
    result.numOfElements = index;
    return result;
}

void main(void) {
    Array array = createArrayByDataFile();
    printf("array int txt ");
    for (int i = 0; i < array.numOfElements; i++) {
        printf("%d ", array.array[i]);
    }
    qSort(array.array, 0, array.numOfElements - 1);
    printf("\nMost freaqment element is %d ", searchMostFreaqmentElement(array.array, array.numOfElements));
    free(array.array);
}

