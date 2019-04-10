
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

void ledControl(int gpio) {
	int i;
	pinMode(gpio, OUTPUT);

	for (i = 0; i < 5; ++i) {
		digitalWrite(gpio, HIGH);
		delay(1000);
		digitalWrite(gpio, LOW);
		delay(1000);
	}
}

int main(int argc, char *argv[]) {
	int gno;
	if (argc < 2) {
		printf("Usage: ./a.out <GPIO_NO>\n");
		return 1;
	}

	gno = atoi(argv[1]);

	wiringPiSetup();
	ledControl(gno);

	return 0;
}






