#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void printWithoutEqual() {
    FILE* file;
    file = fopen("file.txt", "r");
    if (file == NULL) {
        perror("������ �������� �����");
        return 1;
    }
    char ch;
    char last = "";
    while ((ch = fgetc(file)) != EOF) {
        if (ch != last) {
            printf("%c", ch);
            last = ch;
        }
    }
    fclose(file);
}

char* printWithoutEqualForTest(char* fileName) {
    FILE* file;
    char ch;
    file = fopen(fileName, "r");
    if (file == NULL) {
        perror("������ �������� �����");
        return 1;
    }
    char result[100];
    char last = "";
    int index = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (ch != last) {
            result[index] = ch;
            last = ch;
            index++;
        }
    }
    result[index] = '\0';
    fclose(file);
    return result;
}

bool testForPrintWithoutEqualForSingleString() {
    return !strcmp(printWithoutEqualForTest("fileForTestForSingleString.txt"), "afgba");
}

bool testForPrintWithoutEqualFor2Strings() {
    return !strcmp(printWithoutEqualForTest("fileForTestFor2Strings.txt"), "chic\nlasd");
}

int main() {
    if (!testForPrintWithoutEqualForSingleString() || !testForPrintWithoutEqualFor2Strings()) {
        printf("tests are failed");
        return 0;
    }
    printf("text from file without equal:\n");
    printWithoutEqual();
}