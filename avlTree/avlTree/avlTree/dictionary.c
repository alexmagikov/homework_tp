#define _CRT_SECURE_NO_WARNINGS

#include "dictionary.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Dictionary {
    Value value;
    Dictionary* leftChild;
    Dictionary* rightChild;
};

Dictionary* leftRotation(Dictionary* dictionary) {
    Dictionary* rightChild = dictionary->rightChild;
    Dictionary* rightChildLeftChild = dictionary->rightChild->leftChild;
    rightChild->leftChild = dictionary;
    dictionary->rightChild = rightChildLeftChild;

    int dictLeftHeight = (dictionary->leftChild == NULL) ? 0 : dictionary->leftChild->value.height;
    int dictRightHeight = (dictionary->rightChild == NULL) ? 0 : dictionary->rightChild->value.height;
    dictionary->value.height = 1 + (dictLeftHeight > dictRightHeight ? dictLeftHeight : dictRightHeight);

    int rightRightHeight = (rightChild->rightChild == NULL) ? 0 : rightChild->rightChild->value.height;
    rightChild->value.height = 1 + (dictionary->value.height > rightRightHeight ? dictionary->value.height : rightRightHeight);

    dictionary->value.balance = dictRightHeight - dictLeftHeight;
    rightChild->value.balance = rightRightHeight - dictionary->value.height;

    return rightChild;
}

Dictionary* rightRotation(Dictionary* dictionary) {
    Dictionary* leftChild = dictionary->leftChild;
    Dictionary* leftChildRightChild = dictionary->leftChild->rightChild;
    leftChild->rightChild = dictionary;
    dictionary->leftChild = leftChildRightChild;
    int dictLeftHeight = (dictionary->leftChild == NULL) ? 0 : dictionary->leftChild->value.height;
    int dictRightHeight = (dictionary->rightChild == NULL) ? 0 : dictionary->rightChild->value.height;
    dictionary->value.height = 1 + (dictLeftHeight > dictRightHeight ? dictLeftHeight : dictRightHeight);

    int leftLeftHeight = (leftChild->leftChild == NULL) ? 0 : leftChild->leftChild->value.height;
    leftChild->value.height = 1 + (dictionary->value.height > leftLeftHeight ? dictionary->value.height : leftLeftHeight);

    dictionary->value.balance = dictRightHeight - dictLeftHeight;
    leftChild->value.balance = dictionary->value.height - leftLeftHeight;

    return leftChild;
}

Dictionary* BigLeftRotation(Dictionary* dictionary) {
    dictionary->rightChild = rightRotation(dictionary->rightChild);
    return leftRotation(dictionary);
}

Dictionary* BigRightRotation(Dictionary* dictionary) {
    dictionary->leftChild = leftRotation(dictionary->leftChild);
    return rightRotation(dictionary);
}

Dictionary* balance(Dictionary* dictionary) {
    if (dictionary->value.balance == 2) {
        if (dictionary->rightChild->value.balance >= 0) {
            return leftRotation(dictionary);
        }
        return BigLeftRotation(dictionary);
    }
    if (dictionary->value.balance == -2) {
        if (dictionary->leftChild->value.balance <= 0) {
            return rightRotation(dictionary);
        }
        return BigRightRotation(dictionary);
    }
    return dictionary;
}

void insert(Dictionary** dictionary, const char* key, const char* value) {
    Value dictionaryValue = { .balance = 0, .height = 1, .key = malloc(strlen(key) * sizeof(char) + 1), .value = malloc(strlen(value) * sizeof(char) + 1) };
    strcpy(dictionaryValue.key, key);
    strcpy(dictionaryValue.value, value);

    if (dictionaryValue.value == NULL || dictionaryValue.key == NULL) {
        return;
    }
    if (*dictionary == NULL) {
        *dictionary = (Dictionary*)malloc(sizeof(Dictionary));
        if (*dictionary == NULL) {
            return;
        }
        (*dictionary)->value = dictionaryValue;
        (*dictionary)->leftChild = NULL;
        (*dictionary)->rightChild = NULL;
        return;
    }
    if (strcmp(dictionaryValue.key, (*dictionary)->value.key) < 0) {
        insert(&(*dictionary)->leftChild, key, value);
    }
    else if (strcmp(dictionaryValue.key, (*dictionary)->value.key) > 0) {
        insert(&(*dictionary)->rightChild, key, value);
    }
    else if (!strcmp(dictionaryValue.key, (*dictionary)->value.key)) {
        free((*dictionary)->value.value);
        free((*dictionary)->value.key);
        (*dictionary)->value = dictionaryValue;
    }

    int rightHeight = ((*dictionary)->rightChild == NULL) ? 0 : (*dictionary)->rightChild->value.height;
    int leftHeight = ((*dictionary)->leftChild == NULL) ? 0 : (*dictionary)->leftChild->value.height;

    (*dictionary)->value.height = (rightHeight > leftHeight ? rightHeight : leftHeight) + 1;
    (*dictionary)->value.balance = rightHeight - leftHeight;

    *dictionary =  balance(*dictionary);
}

bool find(Dictionary* dictionary, const char* key) {
    if (dictionary == NULL) {
        return false;
    }
    if (strcmp(key, dictionary->value.key) < 0) {
        return find(dictionary->leftChild, key);
    }
    else if (strcmp(key, dictionary->value.key) > 0) {
        return find(dictionary->rightChild, key);
    }
    else if (!strcmp(key, dictionary->value.key)) {
        return true;
    }
}

char* getValue(Dictionary* dictionary, const char* key) {
    if (dictionary == NULL) {
        return NULL;
    }
    if (strcmp(key, dictionary->value.key) < 0) {
        return getValue(dictionary->leftChild, key);
    }
    else if (strcmp(key, dictionary->value.key) > 0) {
        return getValue(dictionary->rightChild, key);
    }
    else if (!strcmp(key, dictionary->value.key)) {
        return dictionary->value.value;
    }
}

void freeDictionary(Dictionary** dictionary) {
    free((*dictionary)->value.value);
    free((*dictionary)->value.key);
    free(*dictionary);
    *dictionary = NULL;
}

void removeFromDictionary(Dictionary** dictionary, const char* key) {
    if (*dictionary == NULL) {
        return;
    }
    if (strcmp(key, (*dictionary)->value.key) > 0) {
        removeFromDictionary(&(*dictionary)->rightChild, key);
    }
    else if (strcmp(key, (*dictionary)->value.key) < 0) {
        removeFromDictionary(&(*dictionary)->leftChild, key);
    }
    else if (!strcmp(key, (*dictionary)->value.key)) {
        if ((*dictionary)->leftChild == NULL && (*dictionary)->rightChild == NULL) {
            freeDictionary(dictionary);
        }

        else if ((*dictionary)->leftChild != NULL && (*dictionary)->rightChild == NULL) {
            free((*dictionary)->value.value);
            (*dictionary)->value = (*dictionary)->leftChild->value;
            (*dictionary)->leftChild->value.value = NULL;
            (*dictionary)->leftChild->value.key = NULL;
            freeDictionary(&(*dictionary)->leftChild);
        }

        else if ((*dictionary)->leftChild == NULL && (*dictionary)->rightChild != NULL) {
            free((*dictionary)->value.value);
            (*dictionary)->value = (*dictionary)->rightChild->value;
            (*dictionary)->rightChild->value.value = NULL;
            (*dictionary)->rightChild->value.key = NULL;
            freeDictionary(&(*dictionary)->rightChild);
        }

        else if ((*dictionary)->leftChild != NULL && (*dictionary)->rightChild != NULL) {
            free((*dictionary)->value.value);
            free((*dictionary)->value.key);
            if ((*dictionary)->rightChild->leftChild == NULL) {
                (*dictionary)->value = (*dictionary)->rightChild->value;
                Dictionary* tmp = (*dictionary)->rightChild;
                (*dictionary)->rightChild = tmp->rightChild;
                tmp->value.value = NULL;
                tmp->value.key = NULL;
                freeDictionary(&tmp);
            }
            else {
                Dictionary* tmp = (*dictionary)->rightChild;
                while (tmp->leftChild->leftChild != NULL) {
                    tmp = tmp->leftChild;
                }
                (*dictionary)->value = tmp->leftChild->value;
                if (tmp->leftChild->rightChild == NULL) {
                    tmp->leftChild->value.value = NULL;
                    tmp->leftChild->value.key = NULL;
                    freeDictionary(&tmp->leftChild);
                }
                else {
                    Dictionary* rightChildTmp = tmp->leftChild->rightChild;
                    tmp->leftChild->value.value = NULL;
                    tmp->leftChild->value.key = NULL;
                    freeDictionary(&tmp->leftChild);
                    tmp->leftChild = rightChildTmp;
                }
            }
        }
        return;
    }
    int rightHeight = ((*dictionary)->rightChild == NULL) ? 0 : (*dictionary)->rightChild->value.height;
    int leftHeight = ((*dictionary)->leftChild == NULL) ? 0 : (*dictionary)->leftChild->value.height;

    (*dictionary)->value.height = (rightHeight > leftHeight ? rightHeight : leftHeight) + 1;
    (*dictionary)->value.balance = rightHeight - leftHeight;

    *dictionary = balance(*dictionary);
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

char* getRightChild(Dictionary* dictionary, const char* key) {
    if (dictionary == NULL) {
        return NULL;
    }
    if (strcmp(key, dictionary->value.key) < 0) {
        return getRightChild(dictionary->leftChild, key);
    }
    else if (strcmp(key, dictionary->value.key) > 0) {
        return getRightChild(dictionary->rightChild, key);
    }
    else if (!strcmp(key, dictionary->value.key)) {
        return dictionary->rightChild->value.key;
    }
}

char* getLeftChild(Dictionary* dictionary, const char* key) {
    if (dictionary == NULL) {
        return NULL;
    }
    if (strcmp(key, dictionary->value.key) < 0) {
        return getLeftChild(dictionary->leftChild, key);
    }
    else if (strcmp(key, dictionary->value.key) > 0) {
        return getLeftChild(dictionary->rightChild, key);
    }
    else if (!strcmp(key, dictionary->value.key)) {
        return dictionary->leftChild->value.key;
    }
}
