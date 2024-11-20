#include "tree.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node {
	char* value;
	Node* leftChild;
	Node* rightChild;
} Node;

Node* createTree(char* value, int* index) {
	if ((*index) >= strlen(value)) {
		return NULL;
	}
	char token = value[*index];
	(*index)++;
	if (isdigit(token)) {
		Node* node = calloc(1, sizeof(Node));
		if (node == NULL) {
			return NULL;
		}
		char* number = malloc(2);
		if (number == NULL) {
			free(node);
			return NULL;
		}
		number[0] = token;
		int numIndex = 1;
		while (*index < strlen(value) && isdigit(value[*index])) {
			number = realloc(number, (numIndex + 1) * sizeof(char));
			if (number == NULL) {
				free(node);
				return NULL;
			}
			number[numIndex] = value[*index];
			numIndex++;
			(*index)++;
		}
		number[numIndex] = '\0';
		node->value = number;
		return node;
	}
	else if (token == '(' || token == ')' || token == ' ') {
		return createTree(value, index);
	}
	else {
		Node* node = calloc(1, sizeof(Node));
		if (node == NULL) {
			free(node);
			return NULL;
		}
		node->value = malloc(2 * sizeof(char));
		if (node->value == NULL) {
			free(node);
			return NULL;
		}
		node->value[0] = token;
		node->value[1] = '\0';
		node->leftChild = createTree(value, index);
		node->rightChild = createTree(value, index);
		return node;
	}
}

void printTree(Node* node) {
	if (node == NULL) {
		return;
	}
	printf("%s ", node->value);
	printTree(node->leftChild);
	printTree(node->rightChild);
}

int calculateTree(Node* node) {
	if (node == NULL) {
		return;
	}
	int result = 0;
	if (isdigit(node->value[0])) {
		return atoi(node->value);
	}
	else if (!strcmp(node->value, "+")) {
		result = calculateTree(node->leftChild) + calculateTree(node->rightChild);
	}
	else if (!strcmp(node->value, "-")) {
		result = calculateTree(node->leftChild) - calculateTree(node->rightChild);
	}
	else if (!strcmp(node->value, "*")) {
		result = calculateTree(node->leftChild) * calculateTree(node->rightChild);
	}
	else if (!strcmp(node->value, "/")) {
		result = calculateTree(node->leftChild) / calculateTree(node->rightChild);
	}
}
