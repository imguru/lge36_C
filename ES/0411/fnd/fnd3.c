// FND
//  공통 애노드: 공통 선이 +에 연결되어 있다. 각 LED에 LOW를 주면
//               불이 켜진다.
//  공통 캐소드: 공통 선이 -에 연결되어 있다. 각 LED에 HIGH를 주면
//               불이 켜진다.

// BCM:   7,  8,  9, 10, 11, 14, 15, 17
// GPIO: 11, 10, 13, 12, 14, 15, 16, 0
#include <string.h>
#include <stdio.h>
#include <wiringPi.h>

int led[8] = { 11, 10, 13, 12, 14, 15, 16, 0 };
//             a    b   c   d   e   f   g  dot
int num[10][8] = {
	{ 1, 1, 1, 1, 1, 1, 0, 0 }, 
	{ 0, 1, 1, 0, 0, 0, 0, 0 },
	{ 1, 1, 0, 1, 1, 0, 1, 0 },
	{ 1, 1, 1, 1, 0, 0, 1, 0 },
	{ 0, 1, 1, 0, 0, 1, 1, 0 },
	{ 1, 0, 1, 1, 0, 1, 1, 0 },
	{ 1, 0, 1, 1, 1, 1, 1, 0 },
	{ 1, 1, 1, 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 1, 1, 1, 1, 0 },
	{ 1, 1, 1, 1, 0, 1, 1, 0 }
};

// num: 0 ~ 9
void showDigit(int select, int value) {
	int i;
	if (value < 0 || value > 9) {
		printf("out of index: %d\n", value);
		return;
	}

	int *arr = num[value];
	for (i = 1; i <= 3; ++i) {
		digitalWrite(i, select == i);
	}

	for (i = 0; i < 8; ++i) {
		digitalWrite(led[i], arr[i]);
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
















