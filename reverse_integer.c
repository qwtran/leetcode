#include <stdio.h>

int power(int base, int exp) {
	if(exp == 0) {
		return 1;
	}
	int result = 1;
	for(int i = 1; i <= exp; ++i) {
		result *= base;
	}
	return result;
}

int reverse(int x) {
	int reversedList[10];

	int digits = 0;
	while(x) {
		reversedList[digits] = x % 10;
		x = x / 10;
		++digits;
	}

	int reversedNum = 0;
	int j = 0;
	for(int i = digits-1; i >= 0; --i) {
		int currentPower = power(10, j++);
		int numToAdd = 0;
		if(__builtin_smul_overflow(currentPower, reversedList[i], &numToAdd)) {
			return 0;
		} else {
			if(__builtin_sadd_overflow(reversedNum, numToAdd, &reversedNum)) {
				return 0;
			}
		}
	}

	return reversedNum;
}

int main()
{
	printf("%i\n", reverse(123));
	printf("%i\n", reverse(-123));
	printf("%i\n", reverse(0));
	printf("%i\n", reverse(120));
	printf("%i\n", reverse(1234567898));
}

