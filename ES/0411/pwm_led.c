#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define RGB_LED1 26
#define RGB_LED2 23

int main(void) {
	int bright;

	printf("Raspberry Pi wiringPi PWM test program...\n");

	if (wiringPiSetup() == -1) {
		exit(1);
	}

	// PWM - ALT0
	pinMode(RGB_LED1, PWM_OUTPUT);
	pinMode(RGB_LED2, PWM_OUTPUT);

	pwmWrite(RGB_LED1, 0);
	pwmWrite(RGB_LED2, 0);

	while (1) {
		for (bright = 0; bright < 1024; ++bright) {
			pwmWrite(RGB_LED1, bright);
			// pwmWrite(RGB_LED2, bright);
			delay(1);
		}

		for (bright = 1023; bright >= 0; --bright) {
			pwmWrite(RGB_LED1, bright);
			// pwmWrite(RGB_LED2, bright);
			delay(1);
		}
	}

	return 0;
}










