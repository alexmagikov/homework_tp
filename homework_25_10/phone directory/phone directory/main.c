#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Note {
    char* name;
    char* phone;
} Note;

typedef struct Base {
    Note* notes;
    int indexOfLastElement;
} Base;

void returnErrorOfMemory(char* array) {
    printf("memory failed");
    free(array);
    exit(0);
}

Base createBase(char* fileName) {
    FILE* file = fopen(fileName, "r+");
    if (file == NULL) {
        Base base;
        base.indexOfLastElement = 0;
        return base;
    }
    char buffer[31];
    int indexOfNote = 0;
    Note* arrayOfNotes = NULL;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        arrayOfNotes = (Note*)realloc(arrayOfNotes, (indexOfNote + 1) * sizeof(Note));
        if (arrayOfNotes == NULL) {
            fclose(file);
            returnErrorOfMemory(arrayOfNotes);
        }
        arrayOfNotes[indexOfNote].name = malloc(20);
        arrayOfNotes[indexOfNote].phone = malloc(12);
        if (arrayOfNotes[indexOfNote].name == NULL) {
            fclose(file);
            returnErrorOfMemory(arrayOfNotes[indexOfNote].name);
        }
        if (arrayOfNotes[indexOfNote].phone == NULL) {
            fclose(file);
            returnErrorOfMemory(arrayOfNotes[indexOfNote].phone);
        }

        char name[20];
        char phone[12];
        int indexBuffer = 0;
        while (buffer[indexBuffer] != ' ') {
            name[indexBuffer] = buffer[indexBuffer];
            indexBuffer++;
        }
        name[indexBuffer] = '\0';
        indexBuffer++;
        int indexName = indexBuffer;
        while (buffer[indexBuffer] != '\n' && buffer[indexBuffer] != '\0') {
            phone[indexBuffer - indexName] = buffer[indexBuffer];
            indexBuffer++;
        }
        phone[indexBuffer - indexName] = '\0';
        strcpy(arrayOfNotes[indexOfNote].name, name);
        strcpy(arrayOfNotes[indexOfNote].phone, phone);
        indexOfNote++;

    }
    fclose(file);
    Base result;
    result.notes = arrayOfNotes;
    result.indexOfLastElement = indexOfNote;
    return result;
}

bool testForCreateBaseForNormalValue() {
    Base base = createBase("baseForTestForNormalValue.txt");
    return base.indexOfLastElement == 1 && (!strcmp(base.notes[0].name, "mark")) && (!strcmp(base.notes[0].phone, "123"));
}

bool testForCreateBaseForBorderValue() {
    Base base = createBase("thisFileDoesNotExist.txt");
    return base.indexOfLastElement == 0;
}

void entryToBase(Base* base, int* indexOfNote) {
    char* name[20];
    char* phone[12];
    printf("input name ");
    scanf("%20s", name);
    printf("input phone ");
    scanf("%11s", phone);
    if (*indexOfNote + 1 > 100) {
        printf("base if full");
        exit(0);
    }
    (*base).notes = (Note*)realloc((*base).notes, (*indexOfNote + 1) * sizeof(Note));
    if ((*base).notes == NULL) {
        returnErrorOfMemory((*base).notes);
    }
    (*base).notes[*indexOfNote].name = malloc(21);
    (*base).notes[*indexOfNote].phone = malloc(12);
    if ((*base).notes[*indexOfNote].name == NULL) {
        returnErrorOfMemory((*base).notes[*indexOfNote].name);
    }
    if ((*base).notes[*indexOfNote].phone == NULL) {
        returnErrorOfMemory((*base).notes[*indexOfNote].phone);
    }
    strcpy((*base).notes[*indexOfNote].name, name);
    strcpy((*base).notes[*indexOfNote].phone, phone);
    (*indexOfNote)++;
}

void entryToBaseForTests(Base* base, int* indexOfNote, char* name, char* phone) {
    if (*indexOfNote + 1 > 100) {
        printf("base if full");
        exit(0);
    }
    (*base).notes = (Note*)realloc((*base).notes, (*indexOfNote + 1) * sizeof(Note));
    if ((*base).notes == NULL) {
        returnErrorOfMemory((*base).notes);
    }
    (*base).notes[*indexOfNote].name = malloc(21);
    (*base).notes[*indexOfNote].phone = malloc(12);
    if ((*base).notes[*indexOfNote].name == NULL) {
        returnErrorOfMemory((*base).notes[*indexOfNote].name);
    }
    if ((*base).notes[*indexOfNote].phone == NULL) {
        returnErrorOfMemory((*base).notes[*indexOfNote].phone);
    }
    strcpy((*base).notes[*indexOfNote].name, name);
    strcpy((*base).notes[*indexOfNote].phone, phone);
    (*indexOfNote)++;
}

bool testForEntryToBaseForNormalValue() {
    Base base;
    base.notes = NULL;
    int index = 0;
    entryToBaseForTests(&base, &index, "mark", "123");
    return !strcmp(base.notes[0].name, "mark") && !strcmp(base.notes[0].phone, "123");
}

void returnNumberByName(Base base, int index) {
    bool isFind = false;
    char name[20];
    printf("input name ");
    scanf("%s", name);
    for (int i = 0; i < index; i++) {
        if (!strcmp(name, base.notes[i].name)) {
            printf("number: %s\n", base.notes[i].phone);
            isFind = true;
            break;
        }

    }
    if (!isFind) {
        printf("number didnt find\n");
    }
}

char* returnNumberByNameForTests(Base base, int index, char name[20]) {
    bool isFind = false;
    for (int i = 0; i < index; i++) {
        if (!strcmp(name, base.notes[i].name)) {
            return base.notes[i].phone;
            isFind = true;
            break;
        }

    }
    if (!isFind) {
        printf("number didnt find\n");
    }
}

bool testForReturnNumberByName() {
    Base base = createBase("baseForTestForNormalValue.txt");
    return !strcmp(returnNumberByNameForTests(base, 1, "mark"), "123");
}

void returnNameByNumber(Base base, int index) {
    char number[12];
    printf("input number ");
    scanf("%s", number);
    bool isFind = false;
    for (int i = 0; i < index; i++) {
        if (!strcmp(number, base.notes[i].phone)) {
            printf("name: %s\n", base.notes[i].name);
            isFind = true;
            break;
        }
    }
    if (!isFind) {
        printf("number didnt find\n");
    }
}

char* returnNameByNumberForTests(Base base, int index, char number[12]) {
    bool isFind = false;
    for (int i = 0; i < index; i++) {
        if (!strcmp(number, base.notes[i].phone)) {
            return base.notes[i].name;
            isFind = true;
            break;
        }
    }
    if (!isFind) {
        printf("number didnt find\n");
    }
}

bool testForReturnNameByNumber() {
    Base base = createBase("baseForTestForNormalValue.txt");
    return !strcmp(returnNameByNumberForTests(base, 1, "123"), "mark");
}

void printToFile(Base* base, int index) {
    FILE* file = fopen("base.txt", "a");
    for (int i = 0; i < (index - (*base).indexOfLastElement); i++) {
        if ((*base).indexOfLastElement + i > 100) {
            printf("base is full");
            break;
        }
        else {
            if  ((*base).indexOfLastElement > 0 && i > 0) {
                fprintf(file, "\n");
            }
            fprintf(file, (*base).notes[(*base).indexOfLastElement + i].name);
            fprintf(file, " ");
            fprintf(file, (*base).notes[(*base).indexOfLastElement + i].phone);
            fprintf(file, "\n");
        }
    }
    (*base).indexOfLastElement = index;
    fclose(file);
}

void printfBase(Base base, int index) {
    for (int i = 0; i < index; i++) {
        printf("%s %s\n", base.notes[i].name, base.notes[i].phone);
    }
}

void main(void) {
    if (!testForEntryToBaseForNormalValue() || !testForReturnNameByNumber() || !testForCreateBaseForNormalValue() || !testForCreateBaseForBorderValue() || !testForReturnNumberByName()) {
        printf("tests are not accepted");
        exit(0);
    }

    Base base = createBase("base.txt");
    int index = base.indexOfLastElement;;
    
    while (true) {
        int currentDo = 0;
        printf("input command ");
        scanf("%d", &currentDo);

        if (currentDo == 0) {
            for (int i = 0; i < index; i++) {
                free(base.notes[i].name);
                free(base.notes[i].phone);
            }
            free(base.notes);
            exit(0);
        }
        else if (currentDo == 1) {
            entryToBase(&base, &index);
        }
        else if (currentDo == 2) {
            printfBase(base, index);
        }
        else if (currentDo == 3) {
            returnNumberByName(base, index);
        }
        else if (currentDo == 4) {
            returnNameByNumber(base, index);
        }
        else if (currentDo == 5) {
            printToFile(&base, index);
        }
    }
}