#include "testsForDictionary.h"
#include <stdbool.h>
#include "dictionary.h"
#include <stdlib.h>
#include <string.h>

bool testForInsertForNormalValue() {
    Dictionary* dict = NULL;
    insert(&dict, 5, "123");
    insert(&dict, 2, "11");
    return !strcmp(getValue(dict,2), "11\0") && !strcmp(getValue(dict, 5), "123\0");
}

bool testForRemoveFromDictionaryForSingleValue() {
    Dictionary* dict = NULL;
    insert(&dict, 5, "123");
    removeFromDictionary(&dict, 5);
    return getValue(dict, 5) == NULL;
}

bool testForRemoveFromDictionaryForNullChildsValue() {
    Dictionary* dict = NULL;
    insert(&dict, 5, "123");
    insert(&dict, 2, "123");
    insert(&dict, 7, "123");
    removeFromDictionary(&dict, 7);
    return getValue(dict, 7) == NULL;
}

bool testForRemoveFromDictionaryForSingleChildsValue() {
    Dictionary* dict = NULL;
    insert(&dict, 5, "123");
    insert(&dict, 2, "123");
    insert(&dict, 7, "123");
    insert(&dict, 9, "1234");
    removeFromDictionary(&dict, 7);
    return getValue(dict, 7) == NULL;
}

bool testForRemoveFromDictionaryForDoubleChildsWithNullRightChildsLeftChildValue() {
    Dictionary* dict = NULL;
    insert(&dict, 5, "123");
    insert(&dict, 2, "123");
    insert(&dict, 7, "123");
    insert(&dict, 9, "1234");
    insert(&dict, 6, "12334");
    removeFromDictionary(&dict, 7);
    return getValue(dict, 7) == NULL;
}

bool testForRemoveFromDictionaryForDoubleChildsWithRightChildsLeftChildValue() {
    Dictionary* dict = NULL;
    insert(&dict, 5, "123");
    insert(&dict, 2, "123");
    insert(&dict, 7, "123");
    insert(&dict, 9, "1234");
    insert(&dict, 6, "12334");
    insert(&dict, 8, "12312");
    removeFromDictionary(&dict, 7);
    return getValue(dict, 7) == NULL;
}

bool testForRemoveFromDictionaryForDoubleChildsWithRightChildsLeftChildRightChildValue() {
    Dictionary* dict = NULL;
    insert(&dict, 5, "123");
    insert(&dict, 2, "123");
    insert(&dict, 7, "123");
    insert(&dict, 9, "1234");
    insert(&dict, 6, "12334");
    insert(&dict, 8, "12312");
    insert(&dict, 9, "213123");
    removeFromDictionary(&dict, 7);
    return getValue(dict, 7) == NULL;
}

bool testForRemoveDictionary() {
    Dictionary* dict = NULL;
    insert(&dict, 5, "123");
    insert(&dict, 2, "12312");
    insert(&dict, 7, "234242");
    removeDictionary(&dict);
    return dict == NULL;
}

bool isPassedTests() {
    bool tests[] = {
        testForInsertForNormalValue(),
        testForRemoveFromDictionaryForSingleValue(),
        testForRemoveFromDictionaryForNullChildsValue(),
        testForRemoveFromDictionaryForSingleChildsValue(),
        testForRemoveFromDictionaryForDoubleChildsWithNullRightChildsLeftChildValue(),
        testForRemoveFromDictionaryForDoubleChildsWithRightChildsLeftChildValue(),
        testForRemoveFromDictionaryForDoubleChildsWithRightChildsLeftChildRightChildValue(),
        testForRemoveDictionary(),
    };
    for (int i = 0; i < 9; i++) {
        if (!tests[i]) {
            printf("test %d failed", i);
            return false;
        }
    }
    return true;
}