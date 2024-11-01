#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void printWithoutEqual() {
    FILE* file;
    file = fopen("file.txt", "r");
    if (file == NULL) {
        printf("Ошибка открытия файла");
        return 1;
    }
    char ch;
    char lastChar = "";
    while ((ch = fgetc(file)) != EOF) {
        if (ch != lastChar) {
            printf("%c", ch);
            lastChar = ch;
        }
    }
    fclose(file);
}

char* printWithoutEqualForTest(char* fileName) {
    FILE* file;
    char ch;
    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Ошибка открытия файла");
        return 1;
    }
    char result[100];
    char lastChar = "";
    int index = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (ch != lastChar) {
            result[index] = ch;
            lastChar = ch;
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