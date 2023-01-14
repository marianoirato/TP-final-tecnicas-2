#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcf8591.h>

#define Address 0x48
#define BASE 64
#define A0 BASE+0
#define A1 BASE+1
#define A2 BASE+2
#define A3 BASE+3

int main(void){
	int val;
	if (wiringPiSetup () == -1) exit (1);	
	pcf8591Setup(BASE, Address);
	while(1)
	{
		val = analogRead(A3);
		printf("A3: %d \n",val);
		delay(1000);
	}
return 0;
}
