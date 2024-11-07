#include "list.h"
#include <stdbool.h>
#include <stdlib.h>

bool testForCreateList(void) {
	return createList() != NULL;
}

bool testForAdd(void) {
	List* list = createList();
	Position position = first(list);
	add(list, position, 1);
	return position != NULL;
}

bool testForGetValueForNormalValue(void) {
	List* list = createList();
	Position position = first(list);
	add(list, position, 1);
	position = next(position);
	return getValue(list, position) == 1;
}

bool testForGetValueForNullValue(void) {
	List* list = createList();
	Position position = first(list);
	return getValue(list, position) == NULL;
}

bool testForRemoveForNormalValue(void) {
	List* list = createList();
	Position position = first(list);
	add(list, position, 1);
	removeFromList(list, position);
	return next(position) == position;
}

bool testForSetValue(void) {
	List* list = createList();
	Position position = first(list);
	add(list, position, 1);
	position = next(position);
	add(list, position, 2);
	setValue(list, position, 3);
	return getValue(list, position) == 3;
}

