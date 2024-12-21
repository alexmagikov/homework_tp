#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>

#include "sorting.h"

void swap(int* num1, int* num2) {
    int swapVariable = *num1;
    *num1 = *num2;
    *num2 = swapVariable;
}

int hoarSort(int array[], int leftIndex, int rightIndex) {
    int pivot = array[rand() % (rightIndex - leftIndex) + leftIndex];
    int endIndex = rightIndex;
    int startIndex = leftIndex;
    while (startIndex <= endIndex) {
        while (array[startIndex] < pivot) {
            startIndex++;
        }
        while (array[endIndex] > pivot) {
            endIndex--;
        }
        if (startIndex <= endIndex) {
            swap(&array[startIndex], &array[endIndex]);
            startIndex++;
            endIndex--;
        }
    }
    return startIndex;
}

void qSort(int array[], int leftIndex, int rightIndex) {
    if (leftIndex < rightIndex) {
        int separator = hoarSort(array, leftIndex, rightIndex);
        qSort(array, leftIndex, separator - 1);
        qSort(array, separator, rightIndex);
    }
}