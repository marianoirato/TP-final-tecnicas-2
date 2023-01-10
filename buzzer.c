#include <stdio.h>
#include <wiringPi.h>
//#include <softTone.h>

#define PIN 3
int notas [] = {392, 392, 440, 392, 523, 494, 392, 392, 440, 587, 523, 523, 659, 784, 659, 523, 494, 440, 698, 698, 659, 523, 587, 523};

int main(void)
{
	wiringPiSetup();	

	softToneCreate(pin);

	for(;;)
	{
		for(int i = 0; i < 25; i++)
		{
			softToneWrite(pin, notas[i]);
			delay(500);
		}
	}

	return 0;
}
