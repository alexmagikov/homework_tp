#define _CRT_SECURE_NO_WARNINGS

#include "dictionary.h"
#include <stdlib.h>
#include <stdio.h>
#include "testsForDictionary.h"
#include <string.h>

int main() {
	if (!isPassedTests()) {
		return -1;
	}
	int command = -1;
	Dictionary* dictionary = NULL;
	while (true) {
		printf("input command:\n1 - add value by key in dictionary\n2 - get value by key from dictionary\n3 - check availability key in dictionary\n4 - delete value by key\n0 - exit\n");
		scanf("%d", &command);
		if (command == 0) {
			removeDictionary(&dictionary);
			return 0;
		}
		else if (command == 1) {
			int key = 0;
			char string[100] = "\0";
			printf("input key: ");
			scanf("%d", &key);
			printf("input value: ");
			scanf("%100s", string);
			DictionaryValue value = { .key = key, .value = malloc(strlen(string) * sizeof(char))};
			strcpy(value.value, string);
			insert(&dictionary, value); 
		}
		else if (command == 2) {
			int key = 0;
			printf("input key: ");
			scanf("%d", &key);
			printf("value: %s\n", getValue(dictionary, key));
		}
		else if (command == 3) {
			int key = 0;
			printf("input key: ");
			scanf("%d", &key);
			if (find(dictionary, key)) {
				printf("in dictionary\n");
			}
			else {
				printf("not in dictionary\n");
			}
		}
		else if (command == 4) {
			int key = 0;
			printf("input key: ");
			scanf("%d", &key);
			removeFromDictionary(&dictionary, key);
		}
	}
	return 0;
}