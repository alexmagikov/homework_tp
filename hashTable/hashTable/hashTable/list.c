#define _CRT_SECURE_NO_WARNINGS

#include "list.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

typedef struct ListElement {
	Value value;
	ListElement* next;
} ListElement;

typedef struct List {
	ListElement* head;
	int length;
} List;

List* createList() {
	List* list = malloc(sizeof(List));
	ListElement* head = calloc(1, sizeof(ListElement));
	list->head = head;
	list->length = 0;
	return list;
}

Position first(List* list) {
	return list->head;
}

void add(List* list, Position position, Value value) {
	ListElement* element = calloc(1, sizeof(ListElement));
	element->value.entry = malloc((strlen(value.entry) + 1) * sizeof(char));
	strcpy(element->value.entry, value.entry);
	element->value.count = value.count;
	element->next = position->next;
	position->next = element;
	list->length++;
}

Value getValue(List* list, Position position) {
	if (position == NULL) {
		Value value = { .count = 0, .entry = NULL };
		return value;
	}
	return position->value;
}

void setValue(List* list, Position position, Value value) {
	position->value = value;
}

bool isLast(List* list, Position position) {
	return position->next == NULL;
}

bool isValid(List* list, Position position) {
	return position != NULL;
}

void removeFromList(List* list, Position position) {
	if (position->next == NULL) {
		printf("pointer to NULL");
		exit(0);
	}
	List* tmp = position->next->next;
	free(position->next->value.entry);
	free(position->next);
	position->next = tmp;
	list->length--;
}

Position next(Position position) {
	return position->next;
}

void freeList(List* list) {
	Position position = first(list);
	while (!isLast(list, position)) {
		removeFromList(list, position);
	}
	free(list);
}

int getLength(List* list) {
	return list->length;
}