#include "tests.h"
#include "dictionary.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

bool testForLeftRotationForNormalValue() {
    Dictionary* dictionary = NULL;
    insert(&dictionary, "2", "value1");
    insert(&dictionary, "1", "value2");
    insert(&dictionary, "4", "value3");
    insert(&dictionary, "5", "value4");
    insert(&dictionary, "6", "value123");
    return !strcmp(getLeftChild(dictionary, "5"), "4") && !strcmp(getRightChild(dictionary, "5"), "6");
}

bool testForRightRotationForNormalValue() {
    Dictionary* dictionary = NULL;
    insert(&dictionary, "5", "value1");
    insert(&dictionary, "8", "value2");
    insert(&dictionary, "4", "value3");
    insert(&dictionary, "3", "value4");
    insert(&dictionary, "2", "value123");
    return !strcmp(getLeftChild(dictionary, "3"), "2") && !strcmp(getRightChild(dictionary, "3"), "4");
}

bool testForBigLeftRotationForNormalValue() {
    Dictionary* dictionary = NULL;
    insert(&dictionary, "5", "value1");
    insert(&dictionary, "8", "value2");
    insert(&dictionary, "6", "value3");
    return !strcmp(getLeftChild(dictionary, "6"), "5") && !strcmp(getRightChild(dictionary, "6"), "8");
}

bool testForBigRightRotationForNormalValue() {
    Dictionary* dictionary = NULL;
    insert(&dictionary, "5", "value1");
    insert(&dictionary, "3", "value2");
    insert(&dictionary, "4", "value3");
    return !strcmp(getLeftChild(dictionary, "4"), "3") && !strcmp(getRightChild(dictionary, "4"), "5");
}

bool testForRemoveFromDictionaryForLeftRotationValue1() {
    Dictionary* dictionary = NULL;
    insert(&dictionary, "5", "value1");
    insert(&dictionary, "3", "value2");
    insert(&dictionary, "6", "value3");
    insert(&dictionary, "7", "value3");
    removeFromDictionary(&dictionary, "3");
    return !strcmp(getLeftChild(dictionary, "6"), "5") && !strcmp(getRightChild(dictionary, "6"), "7");
}   

bool isCompleteTests() {
    
    bool tests[5] = { 
        testForLeftRotationForNormalValue(), 
        testForRightRotationForNormalValue(), 
        testForBigLeftRotationForNormalValue(), 
        testForBigRightRotationForNormalValue(),
        testForRemoveFromDictionaryForLeftRotationValue(),
    };
    for (int i = 0; i < 5; i++) {
        if (!tests[i]) {
            printf("test %d failed", i);
            return false;
        }
    }
    return true;
}