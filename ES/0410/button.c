#include <stdio.h>
#include <wiringPi.h>

#define SW 4    // BCM_GPIO 23
#define LED1 27 // BCM_GPIO 16

// Interrupt
// : 평소에 다른일을 수행하다가, 하드웨어의 변화가 감지되면, 정해진 핸들러를 호출하는 방식.

void blink(void) {
	printf("인터럽트 신호 발생...\n");
}

int main(void) {
	wiringPiSetup();
	// g, ]
	// ctrl + t
	// 특정한 GPIO의 이벤트가 발생하였을 때, 수행할 핸들러를 등록하는 함수.

	// mode
	//  INT_EDGE_RISING
	//  INT_EDGE_FALLING
	//  INT_EDGE_BOTH
	// wiringPiISR(SW, INT_EDGE_FALLING, blink);
	wiringPiISR(SW, INT_EDGE_RISING, blink);
	
	getchar();
}



#if 0
// Polling
//  : 하드웨어의 변화를 지속적으로 읽어드려서 변화를 확인하는 방법.
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
#endif
