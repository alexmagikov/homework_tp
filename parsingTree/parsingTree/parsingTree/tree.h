#pragma once

typedef struct Node Node;

Node* createTree(char* value, int* index);

void printTree(Node* node);

int calculateTree(Node* node);