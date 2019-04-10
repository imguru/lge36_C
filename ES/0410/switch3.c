
#if 0
| Mode | Name    | wPi | BCM |
+------+---------+-----+-----+
| IN   | GPIO. 4 | 4   | 23  |
| IN   | GPIO. 5 | 5   | 24  |
+------+---------+-----+-----+
#endif

#include <wiringPi.h>
#include <stdio.h>

#define SW1 4
#define SW2 5

#define LED  27
// 27 / 10 => 2
// 27 % 10 => 7 * 3

// OUTPUT(R/W) 모드에서는 read가 가능하지만,
// INPUT(R) 모드에서는 write가 불가능하다.

int main() {
	wiringPiSetup();
	int value = 1;

	pinMode(SW1, INPUT);
	pinMode(SW2, INPUT);

	while (1) {
		if (digitalRead(SW1) == LOW) {  // 눌렀을 때
			pinMode(LED, OUTPUT);
			value = !value;
			digitalWrite(LED, value);

			printf("led: %d\n", digitalRead(LED));
		}
		delay(500);
	}

}

























