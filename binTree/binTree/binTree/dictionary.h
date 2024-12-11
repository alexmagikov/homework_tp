#pragma once
#include <stdbool.h>

typedef struct DictionaryValue {
	int key;
	char* value;
} DictionaryValue;

typedef struct Dictionary Dictionary;

// добавление элемента по ключу (если ключ совпал то заменить значение)
void insert(Dictionary** dictionary, int key, const char* value);

// проверка наличия заданного ключа в словаре
bool find(Dictionary* dictionary, int key);

// получить значение по ключу
char* getValue(Dictionary* dictionary, int key);

// удалить ключ и связанное с ним значение. Если ключа нет, то функция ничего не делает
void removeFromDictionary(Dictionary** dictionary, int key);

// вывести словарь на экран 
void print(Dictionary* dictionary);

// удалить словарь
void removeDictionary(Dictionary** dictionary);

void freeDictionary(Dictionary** dictionary);