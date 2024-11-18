#pragma once

#include "testsForDictionary.h"
#include <stdbool.h>

bool testForInsertForNormalValue();

bool testForRemoveFromDictionaryForSingleValue();

bool testForRemoveFromDictionaryForNullChildsValue();

bool testForRemoveFromDictionaryForSingleChildsValue();

bool testForRemoveFromDictionaryForDoubleChildsWithNullRightChildsLeftChildValue();

bool testForRemoveFromDictionaryForDoubleChildsWithRightChildsLeftChildValue();

bool testForRemoveFromDictionaryForDoubleChildsWithRightChildsLeftChildRightChildValue();

bool testForRemoveDictionary();

bool isPassedTests();