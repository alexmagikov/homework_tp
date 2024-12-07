#include <stdbool.h>

bool isSortedArray(int array[], int numOfElements) {
	for (int i = 0; i < numOfElements - 1; i++) {
		if (array[i] > array[i + 1]) {
			return false;
		}
	}
	return true;
}

bool isNormalNumOfElements(int numOfElements) {
	return numOfElements > 0 && numOfElements < 142343242;
}
