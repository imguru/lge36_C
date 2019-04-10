#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include <wiringPi.h>
#include <mcp3422.h>

int main (int argc, char *argv [])
{
	wiringPiSetup () ;
	mcp3422Setup (400, 0x6a, 0, 0) ; // !!

	for (;;)
	{
		printf ("%4d\n",   analogRead(403));
		delay (1000) ;
	}
}

