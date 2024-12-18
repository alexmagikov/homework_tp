#pragma once

#include <stdbool.h>

typedef struct Stack Stack;

void push(Stack* stack, char value);

void pop(Stack* stack);

int peek(Stack* stack);

bool isEmpty(Stack* stack);

Stack* createStack();

void clearStack(Stack* stack);