#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include "list.h"
#include <stdio.h>
#include "tests.h"
#include "functions.h"

int main(void) {
	if (!testForRemoveFromSortingListForNullValue() || !testForRemoveFromSortingListForSingleValue() || !testForRemoveFromSortingListForNormalValue() ||  !testForAddToSortingListForEqualValue() || !testForAddToSortingListForNormalValue() ||  !testForAddToSortingListForSingleValue() ||  !testForSetValue() || !testForCreateList() || !testForAdd() || !testForGetValueForNormalValue() || !testForGetValueForNullValue() || !testForRemoveForNormalValue()) {
		printf("tests are not completed");
		return -1;
	}

	int numOfCommand = -1;
	List* list = createList();
	Position position = first(list);

	while (true) {
		printf("input command: ");
		scanf("%d", &numOfCommand);
		switch (numOfCommand) {
		    case 0: {
				freeListElements(list);
				free(list);
				return 0;
				break;
			}
			case 1: {
				Value value = 0;
				printf("input a num to add: ");
				scanf("%d", &value);
				addToSortingList(list, value);
				break;
			case 2: {
				Value value = 0;
				printf("input a num to remove ");
				scanf("%d", &value);
				removeFromSortingList(list, value);
				break;
			}
			case 3: {
				printList(list);
				break;
			}
			}
		}
	}
}