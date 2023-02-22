#include <stdio.h>
#include "setup.h"
#include "log_in.h"
#include "secuencia_leds.h"
#include "impresion_pantalla.h"

int main (void)
{
	// si se ingresa mal termina el programa luego de N intentos
	if(!log_in())
		return 0;

	// inicializa los GPIO
	setup();

	modo();

	return 0;
}


