
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

int main() {
	wiringPiSetup();

	pinMode(SW1, INPUT);
	pinMode(SW2, INPUT);

	while (1) {
		if (digitalRead(SW1) == LOW) {  // 눌렀을 때
			printf("눌렀음...\n");
		}

		if (digitalRead(SW2) == LOW) {  // 눌렀을 때
			printf("눌렀음...\n");
		}

		delay(500);
	}

}

























