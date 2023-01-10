#include <stdio.h>
#include <wiringPi.h>
#include <pcf8591.h>
#include "setup.h"
#include "secuencia_leds.h"

const int pinouts[] = {0, 1, 2, 3, 4, 5, 6, 7};

void setup()
{
        // inicializamos la libreria
        wiringPiSetup();

        // declaramoos los pines de los leds como salidas
        for(int i = 0; i < N_LEDS; i++)
                        pinMode(pinouts[i], OUTPUT);
	
	// inicializamos el adc
	pcf8591Setup(BASE, ADDRESS);

	set_delay();
}

void set_delay()
{
	tiempo_retardo = 1000;
	/*
	if(analogRead(A0) < 10)
		tiempo_retardo = 100;
	else
		tiempo_retardo = analogRead(A0) * FACTOR_DELAY;
	*/
}
