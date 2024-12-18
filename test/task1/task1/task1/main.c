#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "binToDec.h"
#include <stdio.h>
#include <stdlib.h>
#include "test.h"

int main() {
    if (!areTestsCompleted()) {
        return -1;
    }
    char strBinNum[33] = "\0";
    printf("Input binary notation int num: ");
    scanf("%s", strBinNum);

    char* strDecNum = binToDec(strBinNum);
    printf("Decimal notation int num: %s\n", strDecNum);

    free(strDecNum);
    return 0;
}