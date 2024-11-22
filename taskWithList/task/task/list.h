#pragma once

#include <stdbool.h>

typedef struct List List;

typedef struct ListElement ListElement;

typedef ListElement* Position;

typedef char* Value;

List* createList(void);

Position first(List* list);

Position next(Position position);

void add(List* list, Position position, Value value);

Value getValue(List* list, Position position);

void setValue(List* list, Position position, Value value);

void removeFromList(List* list, Position position);

bool isLast(List* list, Position position);

bool isValid(List* list, Position position);

void freeListElements(List* list);

int getLength(List* list);