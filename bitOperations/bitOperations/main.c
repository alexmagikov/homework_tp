#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>

int8_t decToBin(int num) {
    int8_t result = 0b00000000; 
	result |= num;
    return result;
}

int8_t sumOfBin(int8_t num1, int8_t num2) {
	int reserve = 0;
	int8_t result = 0b00000000;
	for (int i = 0; i < 8; i++) {
		int sum = ((num1 >> i) & 1) + ((num2 >> i) & 1)  + reserve;
		if (sum == 0) {
			result |= (0 << i); 
			reserve = 0;
		}
		else if (sum == 1) {
			result |= (1 << i); 
			reserve = 0;
		}
		else if (sum == 2) {
			result |= (0 << i); 
			reserve = 1; 
		}
		else if (sum == 3) {
			result |= (1 << i); 
			reserve = 1;
		}
	}

	return result;
}

void printBin(int8_t num) {
	for (int i = 7; i >= 0; i--) {
		printf("%d", (num >> i) & 1);
	}
	printf("\n");
}

int binToDec(int8_t num) {
	int result = 0;
	for (int i = 0; i < 8; i++) {
		result += ((num >> i) & 1) * pow(2, i);
	}
	if (((num >> 7) & 1) == 1) {
		return result - 256;
	}
	return result;
}

bool testBinToDecNormalValues1() {
	return binToDec(0b00011011) == 27;
}

bool testBinToDecNormalValues2() {
	return binToDec(0b10011011) == -101;
}

bool testBinToDecBorderValues1() {
	return binToDec(0b11111111) == -1;
}

bool testBinToDecBorderValues2() {
	return binToDec(0b01111111) == 127;
}

void main(void) {
	setlocale(LC_ALL, "Rus");
	int num1;
	int num2;
	printf("введите первое целое число из диапазона от -128 до 127 \n");
	scanf("%d", &num1);
	printf("введите второе целое число из диапазона от -128 до 127 \n");
	scanf("%d", &num2);
	printf("%d \n", decToBin(-128));
	if (num1 > 127 || num1 < -128 || num2 > 127 || num2 < -128) {
		printf("некорректные данные");
	}
	else {
		printf("первое число в двоичном представлении ");
		printBin(decToBin(num1));
		printf("второе число в двоичном представлении ");
		printBin(decToBin(num2));
		printf("сумма чисел в двоичном представлении ");
		printBin(sumOfBin(decToBin(num1), decToBin(num2)));
		if (testBinToDecNormalValues1() && testBinToDecNormalValues2() && testBinToDecBorderValues1() && testBinToDecBorderValues2()) {
			printf("сумма чисел в десятичном представлении ");
			printf("%d ", binToDec(sumOfBin(decToBin(num1), decToBin(num2))));
		}
		else {
			printf("tests for decToBin didnt work");
		}
	}
}