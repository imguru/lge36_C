#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdint.h>

// #define uchar unsigned char
// typedef unsigned char uchar;

#define LedPinRed    26
#define LedPinGreen  23
#define LedPinBlue   22

void ledInit(void)
{
	pinMode(LedPinRed, PWM_OUTPUT) ;
	pinMode(LedPinGreen, PWM_OUTPUT) ;

	// pinMode(LedPinBlue, OUTPUT);
	softPwmCreate(LedPinBlue, 0, 100);
}

void ledColorSet(uint8_t r_val, uint8_t g_val, uint8_t b_val)
{
	pwmWrite(LedPinRed,   r_val);
	pwmWrite(LedPinGreen, g_val);
	softPwmWrite(LedPinBlue,  b_val);
}

int main(void)
{
	wiringPiSetup();
	ledInit();

	while(1){
		ledColorSet(0xff,0x00,0x00);   //red
		delay(500);
		ledColorSet(0x00,0xff,0x00);   //green
		delay(500);
		ledColorSet(0x00,0x00,0xff);   //blue
		delay(500);
		ledColorSet(0xff,0xff,0x00);   //yellow
		delay(500);
		ledColorSet(0xff,0x00,0xff);  
		delay(500);
		ledColorSet(0xc0,0xff,0x3e);
		delay(500);
		ledColorSet(0x94,0x00,0xd3);
		delay(500);
		ledColorSet(0x76,0xee,0x00);
		delay(500);
		ledColorSet(0x00,0xc5,0xcd);
		delay(500);
	}
	return 0;
}

