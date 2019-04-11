#include <string.h>
#include <stdio.h>
#include <wiringPi.h>

int led[8] = { 11, 10, 13, 12, 14, 15, 16, 0 };
//             a    b   c   d   e   f   g  dot

// 아래 처럼 처리하면, 메모리 소모가 크다.
// 비트로 처리해보자.
#if 0
int num[10][8] = {
	{ 1, 1, 1, 1, 1, 1, 0, 0 },  // 0xFC
	{ 0, 1, 1, 0, 0, 0, 0, 0 },  // 0x60
	{ 1, 1, 0, 1, 1, 0, 1, 0 },  // 0xDA
	{ 1, 1, 1, 1, 0, 0, 1, 0 },  // 0xF2
	{ 0, 1, 1, 0, 0, 1, 1, 0 },  // 0x66
	{ 1, 0, 1, 1, 0, 1, 1, 0 },  // 0xB6
	{ 1, 0, 1, 1, 1, 1, 1, 0 },  // 0xBE
	{ 1, 1, 1, 0, 0, 0, 0, 0 },  // 0xE0
	{ 1, 1, 1, 1, 1, 1, 1, 0 },  // 0xFE
	{ 1, 1, 1, 1, 0, 1, 1, 0 }   // 0xF6
};
#endif

int num[10] = {
	0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6
};


// num: 0 ~ 9
void showDigit(int select, int value) {
	int i;
	int n = num[value];

	if (value < 0 || value > 9) {
		printf("out of index: %d\n", value);
		return;
	}

	for (i = 1; i <= 3; ++i) {
		digitalWrite(i, select == i);
	}

	for (i = 0; i < 8; ++i) {
		digitalWrite(led[i], n & (1 << (7 - i))); // !!
	}
}

void count() {
	int n;
	int i;
	int arr[3];
	int value;

	for (n = 0; n <= 999; ++n) {
		value = n;

		memset(arr, 0, sizeof arr);
		i = 0;
		while (value > 0) {
			arr[i++] = value % 10;
			value /= 10;
		}

		for (i = 0 ; i < 100; ++i) {
			showDigit(1, arr[2]);
			delay(1);
			showDigit(2, arr[1]);
			delay(1);
			showDigit(3, arr[0]);
			delay(1);
		}
	}
}

int main(void) {
	int i;
	wiringPiSetup();
	
	for (i = 0; i < 8; ++i) {
		pinMode(led[i], OUTPUT);
	}

	for (i = 0; i < 3; ++i) {
		pinMode(i + 1, OUTPUT);
	}

	count();
}
















