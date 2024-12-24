#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include "list.h"
#include <stdio.h>
#include "tests.h"

void initializationList(List* list, int n) {
	Position position = first(list);
	for (int i = 1; i <= n; i++) {
		add(list, position, i);
		position = next(position);
	}
}

int searchPositionOfLastWarrior(List* list, int m) {
	Position position = first(list);
	int indexOfElement = 1;
	int lastWarrior = -1;
	if (next(first(list)) == NULL) {
		return lastWarrior;
	}
	while (next(first(list)) != first(list) ) {
		if (next(position) == first(list)) {
			position = next(position);
			continue;
		}
		if (indexOfElement == m) {
			lastWarrior = getValue(list, next(position));
			removeFromList(list, position);
			indexOfElement = 0;
		}
		else {
			position = next(position);
		}
		indexOfElement++;
	}
	return lastWarrior;
}

bool testForLittleCountingForSingleValue(void) {
	List* list = createList();
	initializationList(list, 1);
	return searchPositionOfLastWarrior(list, 1) == 1;
}

bool testForLittleCountingForNormalValue(void) {
	List* list = createList();
	initializationList(list, 7);
	return searchPositionOfLastWarrior(list, 4) == 2;
}

bool testForLittleCountingForSingleValueOfManyWarriors(void) {
	List* list = createList();
	initializationList(list, 50);
	return searchPositionOfLastWarrior(list, 1) == 50;
}

bool testForLittleCountingForNullValue(void) {
	List* list = createList();
	return searchPositionOfLastWarrior(list, 4) == -1;
}

int main(void) {
	if (!testForLittleCountingForNullValue() || !testForLittleCountingForSingleValueOfManyWarriors() || !testForLittleCountingForNormalValue() || !testForLittleCountingForSingleValue() || !testForSetValue() || !testForCreateList() || !testForAdd() || !testForGetValueForNormalValue() || !testForGetValueForNullValue() || !testForRemoveForNormalValue()) {
		printf("tests are not completed");
		return -1;
	}
	
	int n = 0;
	int m = 0;
	printf("input num of warriors: ");
	scanf("%d", &n);
	printf("input num of killing position: ");
	scanf("%d", &m);

	List* list = createList();
	initializationList(list, n);
	printf("position of last survivor warrior %d", searchPositionOfLastWarrior(list, m));
	return 0;
}