#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Note {
    char name[21];
    char phone[12];
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
    char name[20] = "\0";
    char phone[12] = "\0";
    int indexOfNote = 0;
    Note* arrayOfNotes = (Note*)malloc(100*sizeof(Note));
    if (arrayOfNotes == NULL) {
        returnErrorOfMemory(arrayOfNotes);
    }

    while (fscanf(file, "%20s %12s", name, phone) != EOF) {
        if (arrayOfNotes == NULL) {
            fclose(file);
            returnErrorOfMemory(arrayOfNotes);
        }
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

void entryToBase(Base* base, int* indexOfNote, char* name, char* phone) {
    if (*indexOfNote + 1 > 100) {
        printf("base if full");
        exit(0);
    }
    base->notes = (Note*)realloc(base->notes, (*indexOfNote + 1) * sizeof(Note));
    if (base->notes == NULL) {
        returnErrorOfMemory(base->notes);
    }
    strcpy(base->notes[*indexOfNote].name, name);
    strcpy(base->notes[*indexOfNote].phone, phone);
    (*indexOfNote)++;
}

bool testForEntryToBaseForNormalValue() {
    Base base;
    base.notes = NULL;
    int index = 0;
    entryToBase(&base, &index, "mark", "123");
    return !strcmp(base.notes[0].name, "mark") && !strcmp(base.notes[0].phone, "123");
}

char* returnNumberByName(Base base, int index, char* name) {
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
    return !strcmp(returnNumberByName(base, 1, "mark"), "123");
}

char* returnNameByNumber(Base base, int index, char* number) {
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
    return !strcmp(returnNameByNumber(base, 1, "123"), "mark");
}

void printToFile(Base* base, int index) {
    FILE* file = fopen("base.txt", "a");
    for (int i = 0; i < (index - base->indexOfLastElement); i++) {
        if (base->indexOfLastElement + i > 100) {
            printf("base is full");
            break;
        }
        else {
            if  (base->indexOfLastElement > 0 && i > 0) {
                fprintf(file, "\n");
            }
            fprintf(file, base->notes[base->indexOfLastElement + i].name);
            fprintf(file, " ");
            fprintf(file, base->notes[base->indexOfLastElement + i].phone);
            fprintf(file, "\n");
        }
    }
    base->indexOfLastElement = index;
    fclose(file);
}

void printBase(Base base, int index) {
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
            char* name[20];
            char* phone[12];
            printf("input name ");
            scanf("%20s", name);
            printf("input phone ");
            scanf("%11s", phone);
            entryToBase(&base, &index, name, phone);
        }
        else if (currentDo == 2) {
            printBase(base, index);
        }
        else if (currentDo == 3) {
            char name[21] = "\0";
            printf("input name ");
            scanf("%s", name);
            printf("number: %s\n", returnNumberByName(base, index, name));
        }
        else if (currentDo == 4) {
            char number[12] = "\0";
            printf("input number ");
            scanf("%s", number);
            printf("name: %s\n", returnNameByNumber(base, index, number));
        }
        else if (currentDo == 5) {
            printToFile(&base, index);
        }
    }
}