#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include "list.h"
#include "tests.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void printList(List* list) {
	Position position = next(first(list));
	for (int i = 0; i < getLength(list); i++) {
		printf("%s\n", getValue(list, position));
		position = next(position);
	}
}

char* getName(char* string) {
	int index = 0;
	char* name = NULL;
	while (string[index] != ' ' && string[index] != '\0') {
		name = (char*)realloc(name, index + 1);
		if (name == NULL) {
			printf("mem fail");
			exit(0);
		}
		name[index] = string[index];
		index++;
	}
	name[index] = '\0';
	return name;
}

char* getPhone(char* string) {
	char* phone = NULL;
	int index = 0;
	while (string[index] != '-') {
		index++;
	}
	index += 2;
	int lenValue = 0;
	while (string[index] != '\n') {
		phone = (char*)realloc(phone, lenValue + 1);
		if (phone == NULL) {
			printf("mem fail");
			exit(0);
		}
		phone[lenValue] = string[index];
		index++;
		lenValue++;
	}
	phone[lenValue] = '\0';
	return phone;
}

List* initializationList() {
	List* list = createList();
	Position position = first(list);

	FILE* file = fopen("file.txt", "r");
	if (file == NULL) {
		printf("file didnt open");
		return;
	}

	size_t stringLength = 100;
	char* buffer = malloc(stringLength);
	if (buffer == NULL) {
		printf("mem fail");
		fclose(file);
		return NULL;
	}
    
	while (fgets(buffer, stringLength, file) != NULL) {
		char* value = malloc(strlen(buffer));
		if (value == NULL) {
			free(buffer);
			printf("mem fail");
			fclose(file);
			return NULL;
		}
		value = strcpy(value, buffer);
		value[strlen(value) - 1] = '\0';
		add(list, position, value);
		position = next(position);
	}
	free(buffer);
	fclose(file);
	return list;
}	

List* merge(List* firstList, List* secondList, int command) {
	List* resultList = createList();
	Position resultListPosition = first(resultList);

	Position firstListPosition = first(firstList);
	firstListPosition = next(firstListPosition);

	Position secondListPosition = first(secondList);
	secondListPosition = next(secondListPosition);

	int firstListIndex = 0;
	int secondListIndex = 0;

	while (firstListIndex < getLength(firstList) && secondListIndex < getLength(secondList)) {
		if (command == 1) {
			char* firstString = getValue(firstList, firstListPosition);
			char* secondString = getValue(secondList, secondListPosition);
			if (strcmp(getName(firstString), getName(secondString))	 < 0) {
				add(resultList, resultListPosition, getValue(firstList, firstListPosition));
				firstListPosition = next(firstListPosition);
				firstListIndex++;
			}
			else {
				add(resultList, resultListPosition, getValue(secondList, secondListPosition));
				secondListPosition = next(secondListPosition);
				secondListIndex++;
			}
		}
		else if (command = 2) {
			char* firstString = getValue(firstList, firstListPosition);
			char* secondString = getValue(secondList, secondListPosition);
			if (strcmp(getPhone(firstString), getPhone(secondString)) < 0) {
				add(resultList, resultListPosition, getValue(firstList, firstListPosition));
				firstListPosition = next(firstListPosition);
				firstListIndex++;
			}
			else {
				add(resultList, resultListPosition, getValue(secondList, secondListPosition));
				secondListPosition = next(secondListPosition);
				secondListIndex++;
			}
		}
		resultListPosition = next(resultListPosition);
	}

	while (firstListIndex < getLength(firstList)) {
		add(resultList, resultListPosition, getValue(firstList, firstListPosition));
		firstListIndex++;
		resultListPosition = next(resultListPosition);
		firstListPosition = next(firstListPosition);
	}

	while (secondListIndex < getLength(secondList)) {
		add(resultList, resultListPosition, getValue(secondList, secondListPosition));
		secondListIndex++;
		resultListPosition = next(resultListPosition);
		secondListPosition = next(secondListPosition);
	}

	return resultList;
}

void mergeSort(List* list, int command) {
	if (getLength(list) <= 1) {
		return;
	}

	int midIndex = getLength(list) / 2;
	
	Position positionList = first(list);
	positionList = next(positionList);

	List* leftList = createList();
	Position leftListPosition = first(leftList);

	List* rightList = createList();
	Position rightListPosition = first(rightList);

	for (int i = 0; i < midIndex; i++) {
		add(leftList, leftListPosition, getValue(list, positionList));
		leftListPosition = next(leftListPosition);
		positionList = next(positionList);
	}

	for (int i = midIndex; i < getLength(list); i++) {
		add(rightList, rightListPosition, (getValue(list, positionList)));
		rightListPosition = next(rightListPosition);
		positionList = next(positionList);
	}

	mergeSort(leftList, command);
	mergeSort(rightList, command);

	List* resultList = merge(leftList, rightList, command);
	Position resultListPosition = first(resultList);
	resultListPosition = next(resultListPosition);
	Position resultPosition = first(list);
	resultPosition = next(resultPosition);
	for (int i = 0; i < getLength(list); i++) {
		setValue(list, resultPosition, getValue(resultList, resultListPosition));
		resultListPosition = next(resultListPosition);
		resultPosition = next(resultPosition);
	}
}

bool testForGetNameForNormalValue() {
	return !strcmp(getName("mark - 123"), "mark");
}

bool testForGetPhoneForNormalValue() {
	return !strcmp(getPhone("mark - 123"), "123");
}

bool testForMergeForNormalValue() {
	List* firstList = createList();
	Position firstListPosition = first(firstList);
	List* secondList = createList();
	Position secondListPosition = first(secondList);
	add(firstList, firstListPosition, "alex - 123");
	add(secondList, secondListPosition, "eva - 123");
	firstListPosition = next(firstListPosition);
	secondListPosition = next(secondListPosition);
	add(firstList, firstListPosition, "fil - 123");
	add(secondList, secondListPosition, "goga - 123");
	
	List* resultList = merge(firstList, secondList, 1);
	Position resultListPosition = first(resultList);
	resultListPosition = next(resultListPosition);
	for (int i = 0; i < getLength(resultList) - 1; i++) {
		if (strcmp(getValue(resultList, resultListPosition), getValue(resultList, next(resultListPosition))) > 0) {
			return false;
		}
	}
	return true;
}

bool testForMergeSortForNormalValue() {
	List* list = createList();
	Position position = first(list);
	add(list, position, "rgegr - 123");
	position = next(position);
	add(list, position, "kgeg - 123");
	position = next(position);
	add(list, position, "alex - 123");
	position = next(position);
	add(list, position, "cclex - 123");
	position = next(position);
	mergeSort(list, 1);
	position = first(list);
	position = next(position);
	for (int i = 0; i < getLength(list) - 1; i++) {
		if (strcmp(getValue(list, position), getValue(list, next(position))) > 0) {
			return false;
		}
	}
	return true;
}

bool testForMergeSortForEqualValue() {
	List* list = createList();
	Position position = first(list);
	add(list, position, "rgegr - 123");
	position = next(position);
	add(list, position, "rgegr - 123");
	position = next(position);
	add(list, position, "rgegr - 123");
	position = next(position);
	add(list, position, "rgegr - 123");
	position = next(position);
	mergeSort(list, 1);
	position = first(list);
	position = next(position);
	for (int i = 0; i < getLength(list) - 1; i++) {
		if (strcmp(getValue(list, position), getValue(list, next(position))) > 0) {
			return false;
		}
	}
	return true;
}

bool testForMergeSortForNullValue() {
	List* list = createList();
	mergeSort(list, 1);
	Position position = first(list);
	return next(position) == NULL;
}

bool testForMergeSortForSingleValue() {
	List* list = createList();
	Position position = first(list);
	add(list, position, "1");
	position = next(position);
	mergeSort(list, 1);
	return !strcmp(getValue(list, position), "1") && getLength(list) == 1;
}

bool testForMergeSortForSortingList() {
	List* list = createList();
	Position position = first(list);
	add(list, position, "abc - 123");
	position = next(position);
	add(list, position, "bcd - 123");
	position = next(position);
	add(list, position, "cde - 123");
	position = next(position);
	add(list, position, "def - 123");
	position = next(position);
	mergeSort(list, 1);
	position = first(list);
	position = next(position);
	for (int i = 0; i < getLength(list) - 1; i++) {
		if (strcmp(getValue(list, position), getValue(list, next(position))) > 0) {
			return false;
		}
	}
	return true;
}

bool testForMergeSortForListWithDublicates() {
	List* list = createList();
	Position position = first(list);
	add(list, position, "abc - 123");
	position = next(position);
	add(list, position, "abc - 123");
	position = next(position);
	add(list, position, "dd - 123");
	position = next(position);
	add(list, position, "ccc - 123");
	position = next(position);
	mergeSort(list, 1);
	position = first(list);
	position = next(position);
	for (int i = 0; i < getLength(list) - 1; i++) {
		if (strcmp(getValue(list, position), getValue(list, next(position))) > 0) {
			return false;
		}
	}
	return true;
}

int main(void) {
	if (!testForMergeSortForListWithDublicates() || !testForMergeSortForSortingList() || !testForMergeSortForSingleValue() || !testForMergeSortForNullValue() || !testForMergeSortForEqualValue() || !testForMergeForNormalValue() || !testForMergeForNormalValue() || !testForGetPhoneForNormalValue() || !testForGetNameForNormalValue() || !testForSetValue() || !testForCreateList() || !testForAdd() || !testForGetValueForNormalValue() || !testForGetValueForNullValue() || !testForRemoveForNormalValue()) {
		printf("tests are not completed");
		return -1;
	}
	List* list = initializationList();

	int command = 2;
	printf("input command of sorting parameter(1 - sorting for names, 2 - sorting for phones): ");
	scanf("%d", &command);
	mergeSort(list, command);
	printList(list);
	freeListElements(list);
	free(list);
	return 0;
}