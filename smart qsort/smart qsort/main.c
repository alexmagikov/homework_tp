#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "tests.h"
#include <stdbool.h>
    
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

void insertionSort(int array[], int leftIndex, int rightIndex) {
    for (int i = leftIndex + 1; i <= rightIndex; i++) {
        int sortedElementIndex = i;
        int sortedIndex = i - 1;
        while (array[sortedElementIndex] < array[sortedIndex] && sortedIndex >= 0) {
            swap(&array[sortedElementIndex], &array[sortedIndex]);
            sortedIndex--;
            sortedElementIndex--;
        }
    }
}

void qSort(int array[], int leftIndex, int rightIndex) {
    if (leftIndex < rightIndex) {
        if (rightIndex - leftIndex + 1 <= 10) {
            insertionSort(array, leftIndex, rightIndex);
        }
        else {
            int separator = hoarSort(array, leftIndex, rightIndex);
            qSort(array, leftIndex, separator - 1);
            qSort(array, separator, rightIndex);
        }
    }
}

int* createArray(int numOfElements) {
    int* array = (int*)malloc(numOfElements * sizeof(int));
    if (array == NULL) {
        return NULL;
    }
    return array;
}

bool testForStandartValueForInsertionSort() {
    int* array = createArray(10);
    qSort(array, 0, 9);
    return isSortedArray(array, 10);
}

bool testForBoundaryValueForQSort1() {
    int array[10] = { 10,10,3,4,6,2,4,6,4,0 };
    qSort(array, 0, 9);
    return isSortedArray(array, 10);
}

bool testForBoundaryValueForQSort2() {
    int array[10] = { 1,1,1,1,1,1,1,1,1,1 };
    qSort(array, 0, 9);
    return isSortedArray(array, 10);
}


bool testForStandartValueForQSort() {
    int* array = createArray(20);
    qSort(array, 0, 19);
    return isSortedArray(array, 20);
}

void main(void) { 
   
    srand(time(0));
    int numOfElements = 0;
    printf("Input number of elements: ");
    scanf("%d", &numOfElements);
    if (isNormalNumOfElements(numOfElements)) {
        int* array = createArray(numOfElements);

        if (array != NULL) {

            printf("Old array: ");
            for (int i = 0; i < numOfElements; i++) {
                array[i] = rand() % 11;
                printf("%d ", array[i]);
            }
            printf("\n");

            qSort(array, 0, numOfElements - 1);

            if (testForStandartValueForInsertionSort() && testForStandartValueForQSort() && isSortedArray(array, numOfElements) && testForBoundaryValueForQSort1() && testForBoundaryValueForQSort2()) {
                printf("Sorted array: ");
                for (int i = 0; i < numOfElements; i++) {
                    printf("%d ", array[i]);
                }
                free(array);
            }
            else {
                printf("not sorted");
            }

        }

        else {
            printf("Memory allocation failed.\n");
        }
    }
    else {
        printf("Not correct input data\n");
    }
}