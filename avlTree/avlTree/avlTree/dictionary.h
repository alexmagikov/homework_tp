#pragma once
#include <stdbool.h>

typedef struct Dictionary Dictionary;

typedef struct Value {
    int balance;
    int height;
    const char* key;
    const char* value;
} Value;

Dictionary* leftRotation(Dictionary* dictionary);

Dictionary* rightRotation(Dictionary* dictionary);

Dictionary* BigLeftRotation(Dictionary* dictionary);

Dictionary* BigRightRotation(Dictionary* dictionary);

Dictionary* balance(Dictionary* dictionary);

// insert value by key in dictionary 
void insert(Dictionary** dictionary, const char* key, const char* value);

// find availability key in dictionary. Return true if key is contained. If key wasnt found return false
bool find(Dictionary* dictionary, const char* key);

// return value by key. If key wasnt found return NULL
char* getValue(Dictionary* dictionary, const char* key);

// remove value from dictionary
void removeFromDictionary(Dictionary** dictionary, const char* key);

// return right child key
char* getRightChild(Dictionary* dictionary, const char* key);

// return left child key
char* getLeftChild(Dictionary* dictionary, const char* key);

// remove dictionary
void removeDictionary(Dictionary** dictionary);