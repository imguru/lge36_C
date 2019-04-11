// 온도를 측정해서 FND에 출력하는 예제
// # gcc fnd5.c -lpthread -lwiringPi
#include <string.h>
#include <stdio.h>
#include <time.h>

#include <wiringPi.h>
#include <mcp3422.h>   // ADC!!

#include <pthread.h>

int led[8] = { 11, 10, 13, 12, 14, 15, 16, 0 };
int num[10] = {
	0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6
};

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

int fnd_value = 0;

// 0 ~ 999
void showDigit3(int value) {
	int n;
	int i;
	int arr[3];

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

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *fnd_thread(void *arg) {
	while (1) {
		pthread_mutex_lock(&mutex);
		showDigit3(fnd_value);
		pthread_mutex_unlock(&mutex);
	}

	return 0;
}

int main() {
	int i;
	pthread_t thread;

	wiringPiSetup();
	mcp3422Setup(400, 0x6a, 0, 0);

	// ----- FND ------
	for (i = 0; i < 8; ++i) {
		pinMode(led[i], OUTPUT);
	}

	for (i = 0; i < 3; ++i) {
		pinMode(i + 1, OUTPUT);
	}
	// -----------------

	pthread_create(&thread, NULL, fnd_thread, NULL);
	pthread_detach(thread);

	while (1) {
		int reading = analogRead(401);  // 센서로부터 데이터를 읽는다.
		double voltage = reading / 1000.;
		double temp = (voltage - 0.5) * 100;  

		printf("temp: %lf\n", temp);
		pthread_mutex_lock(&mutex);
		fnd_value = temp;
		pthread_mutex_unlock(&mutex);
		delay(1000);
	}
}
