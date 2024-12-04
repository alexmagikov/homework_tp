#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include "binTree.h"
#include "sort.h"
#include "tests.h"

int main(void) {
    if (!isCompletedTests()) {
        return -1;
    }
    int length = 5; 
    int array[5] = { 5, 23, 4, 325, 100 };
    sort(array, length);
    printf("Sorted array: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", array[i]);
    }
    return 0;
}