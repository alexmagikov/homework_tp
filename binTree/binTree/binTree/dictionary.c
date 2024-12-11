#define _CRT_SECURE_NO_WARNINGS

#include "dictionary.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Dictionary {
	DictionaryValue value;
	Dictionary* leftChild;
	Dictionary* rightChild;
} Dictionary;

void insert(Dictionary** dictionary, int key, const char* string) {
	DictionaryValue value = { .key = key, .value = malloc(strlen(string) * sizeof(char) + 1) };
	strcpy(value.value, string);

	if (*dictionary == NULL) {
		*dictionary = calloc(1, sizeof(Dictionary));
		if (*dictionary == NULL) {
			return;
		}
		(*dictionary)->value.key = value.key;
		(*dictionary)->value.value = value.value;
		(*dictionary)->rightChild = NULL;
		(*dictionary)->leftChild = NULL;
	}
	else {
		if (value.key > (*dictionary)->value.key) {
			insert(&(*dictionary)->rightChild, value.key, value.value);
		}
		if (value.key < (*dictionary)->value.key) {
			insert(&(*dictionary)->leftChild, value.key, value.value);
		}
		if (value.key == (*dictionary)->value.key) {
			free((*dictionary)->value.value);
			(*dictionary)->value.value = value.value;
		}
	}
}

bool find(Dictionary* dictionary, int key) {
	if (dictionary == NULL) {
		return false;
	}
	if (key > dictionary->value.key) {
		return find(dictionary->rightChild, key);
	}
	if (key < dictionary->value.key) {
		return find(dictionary->leftChild, key);
	}
	if (key == dictionary->value.key) {
		return true;
	}
}

char* getValue(Dictionary* dictionary, int key) {
	if (dictionary == NULL) {
		return NULL;
	}
	if (key > dictionary->value.key) {
		return getValue(dictionary->rightChild, key);
	}
	if (key < dictionary->value.key) {
		return getValue(dictionary->leftChild, key);
	}
	if (key == dictionary->value.key) {
		return dictionary->value.value;
	}
} 

void freeDictionary(Dictionary** dictionary) {
	free((*dictionary)->value.value);
	free(*dictionary);
	*dictionary = NULL;
}

void removeFromDictionary(Dictionary** dictionary, int key) {
	if (*dictionary == NULL) {
		return;
	}
	if (key > (*dictionary)->value.key) {
		removeFromDictionary(&(*dictionary)->rightChild, key);
	}
	else if (key < (*dictionary)->value.key) {
		removeFromDictionary(&(*dictionary)->leftChild, key);
	}
	else if (key == (*dictionary)->value.key) {
		if ((*dictionary)->leftChild == NULL && (*dictionary)->rightChild == NULL) {
			freeDictionary(dictionary);
		}

		else if ((*dictionary)->leftChild != NULL && (*dictionary)->rightChild == NULL) {
			free((*dictionary)->value.value);
			(*dictionary)->value = (*dictionary)->leftChild->value;
			(*dictionary)->leftChild->value.value = NULL;
			freeDictionary(&(*dictionary)->leftChild);
		}

		else if ((*dictionary)->leftChild == NULL && (*dictionary)->rightChild != NULL) {
			free((*dictionary)->value.value);
			(*dictionary)->value = (*dictionary)->rightChild->value;
			(*dictionary)->rightChild->value.value = NULL;
			freeDictionary(&(*dictionary)->rightChild);
		}

		else if ((*dictionary)->leftChild != NULL && (*dictionary)->rightChild != NULL) {
			free((*dictionary)->value.value);
			if ((*dictionary)->rightChild->leftChild == NULL) {
				(*dictionary)->value = (*dictionary)->rightChild->value;
				Dictionary* tmp = (*dictionary)->rightChild;
				(*dictionary)->rightChild = tmp->rightChild;
				tmp->value.value = NULL;
				freeDictionary(&tmp);
			} else {
				Dictionary* tmp = (*dictionary)->rightChild;
				while (tmp->leftChild->leftChild != NULL) {
					tmp = tmp->leftChild;
				}
				(*dictionary)->value = tmp->leftChild->value;
				if (tmp->leftChild->rightChild == NULL) {
					tmp->leftChild->value.value = NULL;
					freeDictionary(&tmp->leftChild);
				}
				else {
					Dictionary* rightChildTmp = tmp->leftChild->rightChild;
					tmp->leftChild->value.value = NULL;
					freeDictionary(&tmp->leftChild);
					tmp->leftChild = rightChildTmp;
				}
			}
		}
	}	
}

void print(Dictionary* dictionary) {
	if (dictionary == NULL) {
		return;
	}
	else {
		print(dictionary->leftChild);
		printf("%d - %s\n", dictionary->value.key, dictionary->value.value);
		print(dictionary->rightChild);
	}
}

void removeDictionary(Dictionary** dictionary) {  
	if (*dictionary == NULL) {
		free(*dictionary);
		return;
	}
	removeDictionary(&(*dictionary)->leftChild);
	removeDictionary(&(*dictionary)->rightChild);
	free(*dictionary);
	*dictionary = NULL;
} 