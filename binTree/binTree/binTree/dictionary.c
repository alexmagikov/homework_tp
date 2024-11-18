#include "dictionary.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Dictionary {
	DictionaryValue value;
	Dictionary* leftChild;
	Dictionary* rightChild;
} Dictionary;

void insert(Dictionary** dictionary, DictionaryValue value) {
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
			insert(&(*dictionary)->rightChild, value);
		}
		if (value.key < (*dictionary)->value.key) {
			insert(&(*dictionary)->leftChild, value);
		}
		if (value.key == (*dictionary)->value.key) {
			(*dictionary)->value.value = value.value;
		}
	}
}

bool find(Dictionary* dictionary, int key) {
	if (dictionary == NULL) {
		return false;
	}
	else {
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
}

char* getValue(Dictionary* dictionary, int key) {
	if (dictionary == NULL) {
		return NULL;
	}
	else {
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
} 

void removeFromDictionary(Dictionary** dictionary, int key) {
	if (*dictionary == NULL) {
		return;
	}
	else { 
		if (key > (*dictionary)->value.key) {
			removeFromDictionary(&(*dictionary)->rightChild, key);
		}
		else if (key < (*dictionary)->value.key) {
			removeFromDictionary(&(*dictionary)->leftChild, key);
		}
		else if (key == (*dictionary)->value.key) {

			if ((*dictionary)->leftChild == NULL && (*dictionary)->rightChild == NULL) {
				free((*dictionary));
				*dictionary = NULL;
			}

			else if ((*dictionary)->leftChild != NULL && (*dictionary)->rightChild == NULL) {
				(*dictionary)->value = (*dictionary)->leftChild->value;
				free((*dictionary)->leftChild);
				(*dictionary)->leftChild = NULL;
			}

			else if ((*dictionary)->leftChild == NULL && (*dictionary)->rightChild != NULL) {
				(*dictionary)->value = (*dictionary)->rightChild->value;
				free((*dictionary)->rightChild);
				(*dictionary)->rightChild = NULL;
			}

			else if ((*dictionary)->leftChild != NULL && (*dictionary)->rightChild != NULL) {

				if ((*dictionary)->rightChild->leftChild == NULL) {
					(*dictionary)->value = (*dictionary)->rightChild->value;
					Dictionary* tmp = (*dictionary)->rightChild;
					(*dictionary)->rightChild = tmp->rightChild;
					free(tmp);
				}

				else {
					Dictionary* tmp = (*dictionary)->rightChild;
					while (tmp->leftChild->leftChild != NULL) {
						tmp = tmp->leftChild;
					}
					(*dictionary)->value = tmp->leftChild->value;
					if (tmp->leftChild->rightChild == NULL) {
						free(tmp->leftChild);
						tmp->leftChild = NULL;
					}
					else {
						Dictionary* rightChildTmp = tmp->leftChild->rightChild;
						free(tmp->leftChild);
						tmp->leftChild = rightChildTmp;
					}
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
	else {
		removeDictionary(&(*dictionary)->leftChild);
		removeDictionary(&(*dictionary)->rightChild);
		free(*dictionary);
		*dictionary = NULL;
	}
}