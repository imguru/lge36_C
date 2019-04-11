
// FND
//  공통 애노드: 공통 선이 +에 연결되어 있다. 각 LED에 LOW를 주면
//               불이 켜진다.
//  공통 캐소드: 공통 선이 -에 연결되어 있다. 각 LED에 HIGH를 주면
//               불이 켜진다.

// BCM:   7,  8,  9, 10, 11, 14, 15, 17
// GPIO: 11, 10, 13, 12, 14, 15, 16, 0

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
void showDigit(int value) {
	int i;
	if (value < 0 || value > 9) {
		printf("out of index: %d\n", value);
		return;
	}

	int *arr = num[value];


	for (i = 0; i < 8; ++i) {
		digitalWrite(led[i], arr[i]);
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

	digitalWrite(1, HIGH);
	while (1) {
		showDigit(3);
		delay(1);
	}
}
















