// librerías externas
#include <stdio.h>

// archivos de cabecera propios
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

	// elegimos modo local o modo remoto
	modo();

	return 0;
}


