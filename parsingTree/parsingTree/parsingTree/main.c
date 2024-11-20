#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "tests.h"

int main() {
    if (!isPassedTests()) {
        return -1;
    }

    FILE* file = fopen("file.txt", "r");
    if (file == NULL) {
        printf("file opening fail");
        return -1;
    }
    char buffer = '_';
    char* prefixExpression = NULL;
    int lenPrefixExpression = 0;
    while ((buffer = fgetc(file)) != EOF) {
        prefixExpression = realloc(prefixExpression, (lenPrefixExpression + 1) * sizeof(char));
        if (prefixExpression == NULL) {
            printf("mem error");
            return -1;
        }
        prefixExpression[lenPrefixExpression] = buffer;
        lenPrefixExpression++;
    }
    fclose(file);
    prefixExpression[lenPrefixExpression] = '\0';
    
    int index = 0;
    Node* node = createTree(prefixExpression, &index);
    printf("tree: ");
    printTree(node);
    printf("\nresult: %d", calculateTree(node));
    return 0;
}