#pragma once
#include "stack.h"
#include <stdlib.h>
#include "tests.h"
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

bool testForClearStack() {
	Stack* stack = createStack();
	push(stack, 1);
	push(stack, 2);
	clearStack(stack);
	return isEmpty(stack);
}

bool areTestsCompleted() {
	bool tests[5] = {
		testForClearStack(),
		testForCreateStack(),
		testForIsEmpty(),
		testForPeek(),
		testForPop()
	};

	for (int i = 0; i < 5; i++) {
		if (!tests[i]) {
			return false;
		}
	}
	return true;
}