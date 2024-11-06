#include "list.h"
#include <stdbool.h>
#include <stdlib.h>
#include "functions.h"

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
	return isLast(list, position);
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

bool testForAddToSortingListForSingleValue(void) {
	List* list = createList();
	addToSortingList(list, 1);
	Position position = first(list);
	position = next(position);
	return getValue(list, position) == 1;
}

bool testForAddToSortingListForNormalValue(void) {
	List* list = createList();
	addToSortingList(list, 1);
	addToSortingList(list, 5);
	addToSortingList(list, 3);
	Position position = first(list);
	position = next(position);
	bool firstElement = getValue(list, position) == 1;
	position = next(position);
	bool secondElement = getValue(list, position) == 3;
	position = next(position);
	bool thirdElement = getValue(list, position) == 5;
	position = next(position);
	return firstElement && secondElement && thirdElement;
}

bool testForAddToSortingListForEqualValue(void) {
	List* list = createList();
	addToSortingList(list, 1);
	addToSortingList(list, 2);
	addToSortingList(list, 5);
	addToSortingList(list, 2);
	Position position = first(list);
	position = next(position);
	bool firstElement = getValue(list, position) == 1;
	position = next(position);
	bool secondElement = getValue(list, position) == 2;
	position = next(position);
	bool thirdElement = getValue(list, position) == 2;
	position = next(position);
	bool fourthElement = getValue(list, position) == 5;
	position = next(position);
	return firstElement && secondElement && thirdElement && fourthElement;
}

bool testForRemoveFromSortingListForNormalValue(void) {
	List* list = createList();
	addToSortingList(list, 1);
	addToSortingList(list, 5);
	addToSortingList(list, 2);
	Position position = first(list);
	position = next(position);
	removeFromSortingList(list, 2);
	bool firstElement = getValue(list, position) == 1;
	position = next(position);
	bool secondElement = getValue(list, position) == 5;
	position = next(position);
	return firstElement && secondElement;
}

bool testForRemoveFromSortingListForSingleValue(void) {
	List* list = createList();
	addToSortingList(list, 1);
	Position position = first(list);
	removeFromSortingList(list, 1);
	position = next(position);
	return position == NULL;
}

bool testForRemoveFromSortingListForNullValue(void) {
	List* list = createList();
	Position position = first(list);
	removeFromSortingList(list, 1);
	position = next(position);
	return position == NULL;
}

