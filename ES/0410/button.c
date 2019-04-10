#include <stdio.h>
#include <wiringPi.h>

#define SW 4    // BCM_GPIO 23
#define LED1 27 // BCM_GPIO 16

int main (void)
{
	if (wiringPiSetup() == -1)
		return 1 ;

	pinMode(SW, INPUT);
	pinMode(LED1, OUTPUT);

	for(;;)
	{
		digitalWrite(LED1, 0);
		if(digitalRead(SW) == 0)
		{
			digitalWrite(LED1, 1);
			delay(1000);
		}
	}
	return 0 ;
}

