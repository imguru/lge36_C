
#include <string.h>
#include <stdio.h>
#include <time.h>

#include <wiringPi.h>
#include <mcp3422.h>   // ADC!!

int main() {
	wiringPiSetup();
	mcp3422Setup(400, 0x6a, 0, 0);

	// ch 1. 조도 센서 => 400
	// ch 2. 온도 센서 => 401
	// ch 3. 습도 센서 => 402
	// ch 4. 가변 저항 => 403
	while (1) {
		// 온도를 읽기 위해서 필요한 코드
		//-------------------------------
		int reading = analogRead(401);  // 센서로부터 데이터를 읽는다.
		double voltage = reading / 1000.;
		double temp = (voltage - 0.5) * 100;  
		// ------------------------------

		printf("reading: %d\n", reading);  // mV
		printf("temp: %lf\n", temp);

		delay(1000);
	}
}
