#include "functions.h"
#include <stdlib.h>
#include <stdio.h>

void printList(List* list) {
	Position position = first(list);
	position = next(position);
	while (position != NULL) {
		printf("%d ", getValue(list, position));
		position = next(position);
	}
	printf("\n");
}

void addToSortingList(List* list, Value value) {
	Position position = first(list);
	while (!isLast(list, position) && getValue(list, next(position)) <= value) {
		position = next(position);
	}
	add(list, position, value);
}

void removeFromSortingList(List* list, Value value) {
	Position position = first(list);
	while (!isLast(list, position)) {
		if (getValue(list, next(position)) == value) {
			removeFromList(list, position);
			break;
		}
		position = next(position);
	}
}