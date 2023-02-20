#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <fcntl.h>
#include <termios.h>

#include "modo_remoto.h"
#include "impresion_pantalla.h"
#include "secuencia_leds.h"

int fd;

void modo_remoto()
{
	char texto_menu[] =   "Elija una secuencia de leds: \r\n1: El auto Fantástico.\r\n2: El Choque.\r\n3: La Apilada.\r\n4: La Carrera.\r\n5: Contador binario.\r\n6: Explosion.\r\n7: Random LED.\r\n8: Feliz cumpleaños.\r\nPulse la tecla cero ('0') para salir.\r\n";
	char opcion_remoto;

	fd = open ("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NONBLOCK);

        if ( fd == -1)
        	printf ("ERROR : no se pudo abrir el dispositivo.\n");

	tcflush(fd, TCIOFLUSH);

	write(fd, texto_menu, sizeof(texto_menu));

	tcdrain(fd);

	do
		read(fd, &opcion_remoto, sizeof(opcion_remoto));
	while(!(opcion_remoto >= '0' && opcion_remoto <= '8'));
	
	switch(opcion_remoto)
	{
		// las ' ' se ponen porque el serial nos devuleve un char, no un int
		case '1':
			write(fd, "Ingresaste el valor: ", 21);
			write(fd, &opcion_remoto, sizeof(opcion_remoto));
			write(fd, ".\r\n", 3);
			tcdrain(fd);
			auto_fantastico();
			break;
		case '2':
			write(fd, "Ingresaste el valor: ", 21);
			write(fd, &opcion_remoto, sizeof(opcion_remoto));
			write(fd, ".\r\n", 3);
			tcdrain(fd);
			el_choque();
			break;
		case '3':
			write(fd, "Ingresaste el valor: ", 21);
			write(fd, &opcion_remoto, sizeof(opcion_remoto));
			write(fd, ".\r\n", 3);
			tcdrain(fd);
			la_apilada();
			break;
		case '4':
			write(fd, "Ingresaste el valor: ", 21);
			write(fd, &opcion_remoto, sizeof(opcion_remoto));
			write(fd, ".\r\n", 3);
			tcdrain(fd);
			la_carrera();
			break;
		case '5':
			write(fd, "Ingresaste el valor: ", 21);
			write(fd, &opcion_remoto, sizeof(opcion_remoto));
			write(fd, ".\r\n", 3);
			tcdrain(fd);
			contador_binario();
			break;
		case '6':
			write(fd, "Ingresaste el valor: ", 21);
			write(fd, &opcion_remoto, sizeof(opcion_remoto));
			write(fd, ".\r\n", 3);
			tcdrain(fd);
			explosion();
			break;
		case '7':
			write(fd, "Ingresaste el valor: ", 21);
			write(fd, &opcion_remoto, sizeof(opcion_remoto));
			write(fd, ".\r\n", 3);
			tcdrain(fd);
			random_led();
			break;
		case '8':
			write(fd, "Ingresaste el valor: ", 21);
			write(fd, &opcion_remoto, sizeof(opcion_remoto));
			write(fd, ".\r\n", 3);
			tcdrain(fd);
			feliz_cumple();
			break;
		default:
			modo();
			break;
	}

        close (fd);
}

char leer_serial()
{
	char dato;

	read(fd, &dato, sizeof(dato));

	return dato;
}
