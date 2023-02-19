#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringSerial.h>

int main ()
{
	unsigned char opcion;
	int UART, select = -1, check;
	
	wiringPiSetup ();
	
	UART = serialOpen("/dev/ttyS0", 9600);

	// comprobamos que estemos conectados correctamente a UART
	if (UART == -1)
	{
		printf("\n Conexion fallida.\n");
		return -1;
	}
	else
	{
		char menu[] =	"Elija una secuencia de leds: \r\n1: El auto Fantástico.\r\n2: El Choque.\r\n3: La Apilada.\r\n4: La Carrera.\r\n5: Contador binario.\r\n6: Explosion.\r\n7: Random LED.\r\n8: Feliz cumpleaños.\r\nPulse cualquier otra tecla numérica para salir.\r\n";
		
		// enviamos la cadena	
		for(int i = 0; i < strlen(menu); i++)
			serialPutchar(UART, menu[i]);

		opcion = serialGetchar(UART);

		switch(opcion)
		{
			// las ' ' se ponen porque el serial nos devuleve un char, no un int
			case '1':
				printf("Hola 1\n");
				break;
			case '2':
				printf("Hola 2\n");
				break;
			default:
				break;
		}
	}
	
	serialClose(UART);
	
	return 0;
}

