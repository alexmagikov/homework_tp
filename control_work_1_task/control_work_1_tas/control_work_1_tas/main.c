#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isPalindrom(int num) {
	char string[30];
	sprintf(string, "%d", num);
	int endIndex = strlen(string) - 1;
	int startIndex = 0;
	while (startIndex < endIndex) {
		if (string[startIndex] != string[endIndex]) {
			return false;
		}
		endIndex--;
		startIndex++;
	}
	return true;
}

bool testForNormalValues1() {
	return isPalindrom(123321);
}

bool testForNormalValues2() {
	return isPalindrom(1235321);
}

bool testForEqualValues() {
	return isPalindrom(111111);
}

bool testForBorderValue() {
	return isPalindrom(1);
}


int main(void) {
	if (!testForNormalValues1() || !testForNormalValues2() || !testForEqualValues() || !testForBorderValue()) {
		printf("tests are failed");
		return 0;
	}
	int num;
	printf("Input num max of 30 chars  ");
	scanf("%30d", &num);
	if (isPalindrom(num)) {
		printf("palindrom");
	}
	else {
		printf("not palindrom");
	}
}