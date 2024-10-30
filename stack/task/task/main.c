#define _CRT_SECURE_NO_WARNINGS

#include "stack.h"
#include <stdio.h>
#include <stdbool.h>

#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool testForCreateStack() {
	Stack* stack = createStack();
	return stack != NULL;
}

bool testForPeek() {
	Stack* stack = createStack();
	push(stack, 1);
	return peek(stack) == 1;
}

bool testForPop() {
	Stack* stack = createStack();
	push(stack, 1);
	push(stack, 2);
	pop(stack);
	return peek(stack) == 1;
}

bool testForIsEmpty() {
	Stack* stack = createStack();
	return isEmpty(stack);
}

bool testForClearStack() {
	Stack* stack = createStack();
	push(stack, 1);
	push(stack, 2);
	clearStack(stack);
	return isEmpty(stack);
}

char* sortingStation(char* string) {
	char* result = NULL;
	int lenOfReslut = 0;
	Stack* stack = createStack();
	for (int i = 0; i < strlen(string); i++) {
		if (isdigit(string[i])) {
			result = (char*)realloc(result, (lenOfReslut + 1) * sizeof(char));
			if (result == NULL) {
				return NULL;
			}
			result[lenOfReslut] = string[i];
			lenOfReslut++;
		}
		else if (string[i] == '-' || string[i] == '+') {
			if (!isEmpty(stack)) {
				while (peek(stack) == '*' || peek(stack) == '/' || peek(stack) == '+' || peek(stack) == '-') {
					result = (char*)realloc(result, (lenOfReslut + 1) * sizeof(char));
					if (result == NULL) {
						return NULL;
					}
					result[lenOfReslut] = peek(stack);
					lenOfReslut++;
					pop(stack);
				}
			}
			push(stack, string[i]);
		}
		else if (string[i] == '*' || string[i] == '/') {
			if (!isEmpty(stack)) {
				while (peek(stack) == '*' || peek(stack) == '/') {
					result = (char*)realloc(result, (lenOfReslut + 1) * sizeof(char));
					if (result == NULL) {
						return NULL;
					}
					result[lenOfReslut] = peek(stack);
					lenOfReslut++;
					pop(stack);
				}
			}
			push(stack, string[i]);
		}
		else if (string[i] == '(') {
			push(stack, string[i]);
		}
		else if (string[i] == ')') {
			while (peek(stack) != '(') {
				if (isEmpty(stack)) {
					return "didn find open bracket";
				}
				result = (char*)realloc(result, (lenOfReslut + 1) * sizeof(char));
				if (result == NULL) {
					return NULL;
				}
				result[lenOfReslut] = peek(stack);
				lenOfReslut++;
				pop(stack);
			}
			pop(stack);
		}
	}
	while (!isEmpty(stack)) {
		if (peek(stack) == '(') {
			return "didn find close bracket";
		}
		result = (char*)realloc(result, (lenOfReslut + 1) * sizeof(char));
		if (result == NULL) {
			return NULL;
		}
		result[lenOfReslut] = peek(stack);
		pop(stack);
		lenOfReslut++;
	}
	result[lenOfReslut] = '\0';
	return result;
}

bool testForSortingStationForNormalValue1() {
	return !strcmp(sortingStation("(1+1)*2"), "11+2*");
}

bool testForSortingStationForNormalValue2() {
	return !strcmp(sortingStation("2+3*3"), "233*+");
}

bool testForSortingStationForNormalValue3() {
	return !strcmp(sortingStation("(1+2)*3-(4/2)"), "12+3*42/-");
}

bool testForSortingStationForNegativeValue() {
	return !strcmp(sortingStation("("), "didn find close bracket");
}

void main(void) {
	if (!testForSortingStationForNegativeValue() || !testForSortingStationForNormalValue3() || !testForSortingStationForNormalValue2() || !testForSortingStationForNormalValue1() || !testForClearStack() ||  !testForIsEmpty() || !testForPeek || !testForCreateStack() || !testForPop()) {
		printf("tests are failed");
		exit(0);
	}
	char* string[100];
	printf("input infix form ");
	scanf("%s", &string);
	printf("postfix form: %s", sortingStation(string));
}