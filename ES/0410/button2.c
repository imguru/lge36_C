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
	int ret;
	wiringPiSetup();

	pinMode(SW, INPUT);

	wiringPiISR(SW, INT_EDGE_RISING, blink);
	
	ret = waitForInterrupt(SW, 3 * 1000);
	// 1. wiringPiISR을 통해 등록한 GPIO에 대해서 인터럽트 발생까지 대기할 수 있다.
	// 2. timeout: -1을 지정하면, 무한정 기다릴 수 있다.
	printf("ret: %d\n", ret);
	// ret=0 -> 타임아웃
	// ret=1 -> 인터럽트가 발생해서 반환했다.
}












