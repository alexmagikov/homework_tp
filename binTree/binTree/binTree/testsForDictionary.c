#include "testsForDictionary.h"
#include <stdbool.h>
#include "dictionary.h"
#include <stdlib.h>
#include <string.h>

bool testForInsertForNormalValue() {
    Dictionary* dict = NULL;
    DictionaryValue el1 = { .key = 5, .value = "123" };
    DictionaryValue el2 = { .key = 2, .value = "11" };
    insert(&dict, el1);
    insert(&dict, el2);
    return !strcmp(getValue(dict,2), "11\0") && !strcmp(getValue(dict, 5), "123\0");
}

bool testForRemoveFromDictionaryForSingleValue() {
    Dictionary* dict = NULL;
    DictionaryValue el = { .key = 5, .value = "123" };
    insert(&dict, el);
    removeFromDictionary(&dict, 5);
    return getValue(dict, 5) == NULL;
}

bool testForRemoveFromDictionaryForNullChildsValue() {
    Dictionary* dict = NULL;
    DictionaryValue el1 = { .key = 5, .value = "123" };
    DictionaryValue el2 = { .key = 2, .value = "123" };
    DictionaryValue el3 = { .key = 7, .value = "123" };
    insert(&dict, el1);
    insert(&dict, el2);
    insert(&dict, el3);
    removeFromDictionary(&dict, 7);
    return getValue(dict, 7) == NULL;
}

bool testForRemoveFromDictionaryForSingleChildsValue() {
    Dictionary* dict = NULL;
    DictionaryValue el1 = { .key = 5, .value = "123" };
    DictionaryValue el2 = { .key = 2, .value = "123" };
    DictionaryValue el3 = { .key = 7, .value = "123" };
    DictionaryValue el4 = { .key = 9, .value = "1234" };
    insert(&dict, el1);
    insert(&dict, el2);
    insert(&dict, el3);
    insert(&dict, el4);
    removeFromDictionary(&dict, 7);
    return getValue(dict, 7) == NULL;
}

bool testForRemoveFromDictionaryForDoubleChildsWithNullRightChildsLeftChildValue() {
    Dictionary* dict = NULL;
    DictionaryValue el1 = { .key = 5, .value = "123" };
    DictionaryValue el2 = { .key = 2, .value = "123" };
    DictionaryValue el3 = { .key = 7, .value = "123" };
    DictionaryValue el4 = { .key = 9, .value = "1234" };
    DictionaryValue el5 = { .key = 6, .value = "12334" };
    insert(&dict, el1);
    insert(&dict, el2);
    insert(&dict, el3);
    insert(&dict, el4);
    insert(&dict, el5);
    removeFromDictionary(&dict, 7);
    return getValue(dict, 7) == NULL;
}

bool testForRemoveFromDictionaryForDoubleChildsWithRightChildsLeftChildValue() {
    Dictionary* dict = NULL;
    DictionaryValue el1 = { .key = 5, .value = "123" };
    DictionaryValue el2 = { .key = 2, .value = "123" };
    DictionaryValue el3 = { .key = 7, .value = "123" };
    DictionaryValue el4 = { .key = 9, .value = "1234" };
    DictionaryValue el5 = { .key = 6, .value = "12334" };
    DictionaryValue el6 = { .key = 8, .value = "1233444" };
    insert(&dict, el1);
    insert(&dict, el2);
    insert(&dict, el3);
    insert(&dict, el4);
    insert(&dict, el5);
    insert(&dict, el6);
    removeFromDictionary(&dict, 7);
    return getValue(dict, 7) == NULL;
}

bool testForRemoveFromDictionaryForDoubleChildsWithRightChildsLeftChildRightChildValue() {
    Dictionary* dict = NULL;
    DictionaryValue el1 = { .key = 5, .value = "123" }; 
    DictionaryValue el2 = { .key = 2, .value = "123" };
    DictionaryValue el3 = { .key = 7, .value = "123" };
    DictionaryValue el4 = { .key = 10, .value = "1234" };
    DictionaryValue el5 = { .key = 6, .value = "12334"};
    DictionaryValue el6 = { .key = 8, .value = "1233444"};
    DictionaryValue el7 = { .key = 9, .value = "12334444" };
    insert(&dict, el1);
    insert(&dict, el2);
    insert(&dict, el3);
    insert(&dict, el4);
    insert(&dict, el5);
    insert(&dict, el6);
    insert(&dict, el7);
    removeFromDictionary(&dict, 7);
    return getValue(dict, 7) == NULL;
}

bool testForRemoveDictionary() {
    Dictionary* dict = NULL;
    DictionaryValue el1 = { .key = 5, .value = "123" };
    DictionaryValue el2 = { .key = 2, .value = "45643" };
    DictionaryValue el3 = { .key = 7, .value = "1234423423" };
    insert(&dict, el1);
    insert(&dict, el2);
    insert(&dict, el3);
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