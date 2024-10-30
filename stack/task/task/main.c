#define _CRT_SECURE_NO_WARNINGS

#include "stack.h"
#include <stdio.h>
#include <stdbool.h>

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


bool isBalanced(char* string) {
	Stack* stack = createStack();
	for (int i = 0; i < strlen(string); i++) {
		if (string[i] == '{' || string[i] == '[' || string[i] == '(') {
			push(stack, string[i]);
		}
		else if (string[i] == '}') {
			if (peek(stack) != '{' || isEmpty(stack)) {
				clearStack(stack);
				free(stack);
				return false;
			}
			else {
				pop(stack);
			}
		}
		else if (string[i] == ')') {
			if (peek(stack) != '(' || isEmpty(stack)) {
				clearStack(stack);
				free(stack);
				return false;
			}
			else {
				pop(stack);
			}
		}
		else if (string[i] == ']') {
			if (peek(stack) != '[' || isEmpty(stack)) {
				clearStack(stack);
				free(stack);
				return false;
			}
			else {
				pop(stack);
			}
		}
	}
	bool result = isEmpty(stack);
	clearStack(stack);
	free(stack);
	return result;
}

bool testForIsBalancedForTrueValue() {
	return isBalanced("({})");
}

bool testForIsBalancedForFalseValue() {
	return !isBalanced("({)}");
}

bool testForIsBalancedForFalseBorderValue1() {
	return !isBalanced("(");
}

bool testForIsBalancedForFalseBorderValue2() {
	return !isBalanced(")");
}

bool testForClearStack() {
	Stack* stack = createStack();
	push(stack, 1);
	push(stack, 2);
	clearStack(stack);
	return isEmpty(stack);
}

void main(void) {
	if (!testForClearStack() || !testForIsBalancedForFalseBorderValue2() || !testForIsBalancedForFalseBorderValue1() || !testForIsBalancedForTrueValue() || !testForIsBalancedForFalseValue() || !testForIsEmpty() || !testForPeek || !testForCreateStack() || !testForPop()) {
		printf("tests are failed");
		exit(0);
	}
	const char* string[100];
	printf("input string ");
	scanf("%100s", &string);
	if (isBalanced(string)) {
		printf("balanced");
	}
	else {
		printf("not balanced");
	}
}