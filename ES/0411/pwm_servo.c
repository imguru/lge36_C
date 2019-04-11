
#include <stdio.h>
#include <stdlib.h>

#include <wiringPi.h>
#include <softServo.h>  // !!!!

#define SERVO_GPIO 25

// $ gcc pwm_servo.c -lwiringPi ~/wiringPi/wiringPi/softServo.c

int main(void) {
	if (wiringPiSetup() == -1) {
		exit(1);
	}

	softServoSetup(SERVO_GPIO, -1, -1, -1, -1, -1, -1, -1);
	// -250 ~ 1250
	while (1) {
#if 0
		printf("0\n");
		softServoWrite(SERVO_GPIO, 0);
		getchar();
#endif

		printf("-250\n");
		softServoWrite(SERVO_GPIO, -250);
		getchar();

#if 0
		printf("500\n");
		softServoWrite(SERVO_GPIO, 500);
		getchar();
#endif

		printf("1250\n");
		softServoWrite(SERVO_GPIO, 1250);
		getchar();
	}
}



