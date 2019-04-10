// wiringPi를 이용해서 LED를 제어하는 프로그램을 작성해봅시다.

#include <wiringPi.h>
#include <stdio.h>

#if 0
 Mode | Name    | wPi | BCM |
 -----+---------+-----+-----+
 IN   | GPIO.27 | 27  | 16  |
#endif

#define LED  27

// # gcc blink2.c -lwiringPi

int main() {
	printf("Raspberry Pi blink\n");

	// wiringPi 라이브러리를 사용할 때 가장 먼저 호출해야 하는 함수.
	wiringPiSetup();

	pinMode(LED, OUTPUT);

	while (1) {
		digitalWrite(LED, HIGH);
		delay(500);					// 500ms
		digitalWrite(LED, LOW);
		delay(500);
	}

	return 0;
}
