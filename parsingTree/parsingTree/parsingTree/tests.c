#define _CRT_SECURE_NO_WARNINGS

#include "tests.h"
#include "tree.h"
#include <stdio.h>

bool testForCreateTreeForNormalValue() {
	int index = 0;
	return createTree("+*(3)(4)-10/(8)(2)", &index) != NULL;
}

bool testForCreateTreeForNullValue() {
	int index = 0;
	return createTree("", &index) == NULL;
}

bool testForCalculateTreeForNormalValue() {
	int index = 0;
	Node* node = createTree("+*(3)(4)-10/(8)(2)", &index);
	return calculateTree(node) == 18;
}

bool testForCalculateTreeForSingleValue() {
	int index = 0;
	Node* node = createTree("1", &index);
	return calculateTree(node) == 1;
}

bool isPassedTests() {
	bool tests[3] = { testForCreateTreeForNormalValue(), testForCalculateTreeForNormalValue(), testForCalculateTreeForSingleValue()};
	for (int i = 0; i < 3; i++) {
		if (!tests[i]) {
			printf("test %d is not passed", i);
			return false;
		}
	}
	return true;
}