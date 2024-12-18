#define _CRT_SECURE_NO_WARNINGS
#include "binToDec.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* binToDec(char* strBinNum) {
    int length = strlen(strBinNum);
    int resultNum = 0;
    for (int i = 0; i < length; i++) {
        if (strBinNum[i] == '1') {
            resultNum += pow(2, length - 1 - i);
        }
    }
    char* result = (char*)malloc(12);
    if (result == NULL) {
        printf("Failed to allocate memory");
        return NULL;
    }

    snprintf(result, 12, "%d", resultNum);
    return result;
}