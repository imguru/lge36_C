#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#include <softPwm.h> // !!

#define RGB_LED1 23    // HW PWM
#define RGB_LED2 26    // HW PWM
#define RGB_LED3 22    // HW PWM X 
					   // OUTPUT 모드에서 직접 비율을 조절해야 한다.
					   // -> SOFT PWM

int main(void) {
	int bright;

	printf("Raspberry Pi wiringPi PWM test program...\n");

	if (wiringPiSetup() == -1) {
		exit(1);
	}

	// PWM - ALT0
	pinMode(RGB_LED1, PWM_OUTPUT);
	pinMode(RGB_LED2, PWM_OUTPUT);

	//-----
	pinMode(RGB_LED3, OUTPUT);  
	softPwmCreate(RGB_LED3, 0, 1024);
	//-----

	pwmWrite(RGB_LED1, 0);
	pwmWrite(RGB_LED2, 0);
	softPwmWrite(RGB_LED3, 0);

	while (1) {
		for (bright = 0; bright < 1024; ++bright) {
			softPwmWrite(RGB_LED3, bright);

			// pwmWrite(RGB_LED2, bright);
			// pwmWrite(RGB_LED2, bright);
			delay(1);
		}

		for (bright = 1023; bright >= 0; --bright) {
			softPwmWrite(RGB_LED3, bright);
			// pwmWrite(RGB_LED2, bright);
			// pwmWrite(RGB_LED2, bright);
			delay(1);
		}
	}

	return 0;
}










