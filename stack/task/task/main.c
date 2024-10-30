#define _CRT_SECURE_NO_WARNINGS

#include "stack.h"
#include <stdio.h>
#include <stdbool.h>

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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

int calculateInPostfix(const char* string) {
	Stack* stack = createStack();
	for (int i = 0; i < strlen(string); i++) {
		if (isdigit(string[i])) {
			push(stack, string[i] - '0');
		}
		else {
			if (!isEmpty(stack)) {
				int tmp = peek(stack);
				pop(stack);
				if (string[i] == '-') {
					tmp = peek(stack) - tmp;
				}
				else if (string[i] == '+') {
					tmp = peek(stack) + tmp;
				}
				else if (string[i] == '/') {
					if (tmp == 0) {
						printf("u cant divide by 0 ");
						clearStack(stack);
						free(stack);
						exit(0);
						return -1;
					}
					tmp = peek(stack) / tmp;
				}
				else if (string[i] == '*') {
					tmp = peek(stack) * tmp;
				}
				pop(stack);
				push(stack, tmp);
			}
		}
	}
	if (isEmpty(stack)) {
		return -1;
	}
	else {
		int result = peek(stack);
		clearStack(stack);
		free(stack);
		return result;
	}
 }

bool testForPostfixCalculatorForNormalValue() {
	return calculateInPostfix("96-12+*") == 9;
}

bool testForPostfixCalculatorForBorderValue() {
	return calculateInPostfix("1") == 1;
}

bool testForPostfixCalculatorForNULLValue() {
	return calculateInPostfix(" ") == -1;
}

bool testForClearStack() {
	Stack* stack = createStack();
	push(stack, 1);
	push(stack, 2);
	clearStack(stack);
	return isEmpty(stack);
}

void main(void) {
	if (!testForClearStack() || !testForPostfixCalculatorForNULLValue() || !testForPostfixCalculatorForBorderValue() || !testForPostfixCalculatorForNormalValue() || !testForIsEmpty() || !testForPeek || !testForCreateStack() || !testForPop()) {
		printf("tests are failed");
		exit(0);
	}
	Stack* stack = createStack();
	const char* string[100];
	printf("input postfix expression ");
	scanf("%s", &string);
	printf("result %d", calculateInPostfix(string));
}