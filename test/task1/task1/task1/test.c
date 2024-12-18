#define _CRT_SECURE_NO_WARNINGS

#include "test.h"
#include <string.h>
#include "binToDec.h"

bool testForNormalValue() {
    char binStr[6] = "10101";
    char* result = binToDec(binStr);

    bool isCorrect = !strcmp(result, "21");
    free(result);
    return isCorrect;
}

bool areTestsCompleted() {
    bool tests[1] = {
        testForNormalValue()
    };

    for (int i = 0; i < 3; i++) {
        if (!tests[i]) {
            return false;
        }
    }
    return true;
}