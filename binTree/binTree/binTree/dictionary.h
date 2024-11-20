#pragma once
#include <stdbool.h>

typedef struct DictionaryValue {
	int key;
	char* value;
} DictionaryValue;

typedef struct Dictionary Dictionary;

// ���������� �������� �� ����� (���� ���� ������ �� �������� ��������)
void insert(Dictionary** dictionary, int key, const char* value);

// �������� ������� ��������� ����� � �������
bool find(Dictionary* dictionary, int key);

// �������� �������� �� �����
char* getValue(Dictionary* dictionary, int key);

// ������� ���� � ��������� � ��� ��������. ���� ����� ���, �� ������� ������ �� ������
void removeFromDictionary(Dictionary** dictionary, int key);

// ������� ������� �� ����� 
void print(Dictionary* dictionary);

// ������� �������
void removeDictionary(Dictionary** dictionary);

void freeDictionary(Dictionary** dictionary);