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
	char texto_menu[] =   "Elija una secuencia de leds.\r\n1: El auto Fantástico.\r\n2: El Choque.\r\n3: La Apilada.\r\n4: La Carrera.\r\n5: Contador binario.\r\n6: Explosion.\r\n7: Random LED.\r\n8: Feliz cumpleaños.\r\nPulse la tecla cero ('0') para salir.\r\n\r\n";
	char opcion_remoto;
	struct termios oldtty, newtty;

	fd = open ("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NONBLOCK);

        if(fd == -1)
        	printf("ERROR : no se pudo abrir el dispositivo.\n");

	if(termset(fd , 9600, &oldtty, &newtty) == -1)
  		printf(" ERROR : no se pudo configurar el TTY \n" );

	tcflush(fd, TCIOFLUSH);

	write(fd, texto_menu, sizeof(texto_menu));

	tcdrain(fd);

	do
		read(fd, &opcion_remoto, sizeof(opcion_remoto));
	while(!(opcion_remoto >= '0' && opcion_remoto <= '8'));
	

	tcdrain(fd);
	
	switch(opcion_remoto)
	{
		// las ' ' se ponen porque el serial nos devuleve un char, no un int
		case '1':
			write(fd, "Ingresaste al modo ", 19);
			write(fd, "Auto Fantastico.\r\n", 18);
			write(fd, "Ingrese la tecla 's' para salir.\r\n", 34);
			imprimir_retardo(0);
			auto_fantastico();
			break;
		case '2':
			write(fd, "Ingresaste al modo ", 19);
			write(fd, "El Choque.\r\n", 12);
			write(fd, "Ingrese la tecla 's' para salir.\r\n", 34);
			imprimir_retardo(0);
			el_choque();
			break;
		case '3':
			write(fd, "Ingresaste al modo ", 19);
			write(fd, "La Apilada.\r\n", 13);
			write(fd, "Ingrese la tecla 's' para salir.\r\n", 34);
			imprimir_retardo(0);
			la_apilada();
			break;
		case '4':
			write(fd, "Ingresaste al modo ", 19);
			write(fd, "La Carrera.\r\n", 13);
			write(fd, "Ingrese la tecla 's' para salir.\r\n", 34);
			imprimir_retardo(0);
			la_carrera();
			break;
		case '5':
			write(fd, "Ingresaste al modo ", 19);
			write(fd, "Contador Binario.\r\n", 19);
			write(fd, "Ingrese la tecla 's' para salir.\r\n", 34);
			imprimir_retardo(0);
			contador_binario();
			break;
		case '6':
			write(fd, "Ingresaste al modo ", 19);
			write(fd, "Expolosion.\r\n", 13);
			write(fd, "Ingrese la tecla 's' para salir.\r\n", 34);
			imprimir_retardo(0);
			explosion();
			break;
		case '7':
			write(fd, "Ingresaste al modo ", 19);
			write(fd, "Random LED.\r\n", 13);
			write(fd, "Ingrese la tecla 's' para salir.\r\n", 34);
			imprimir_retardo(0);
			random_led();
			break;
		case '8':
			write(fd, "Ingresaste al modo ", 19);
			write(fd, "Feliz Cumpleanos.\r\n", 19);
			write(fd, "Ingrese la tecla 's' para salir.\r\n", 34);
			imprimir_retardo(0);
			feliz_cumple();
			break;
		default:
			write(fd, "Saliste del modo remoto.\r\n\r\n", 28);
			limpiar_serial();
			elegir_modo = 1;
			close(fd);
			modo();
			break;
	}

        close(fd);
}

int termset(int fd, int baudrate, struct termios *ttyold, struct termios *ttynew)
{
	switch(baudrate)
	{
		case 115200: 
			baudrate = B115200;
			break ;
		case 57600: 
			baudrate = B57600;
			break ;
		case 38400:
			baudrate = B38400;
			break ;
		case 19200: 
			baudrate = B19200;
			break ;
		case 9600:
			baudrate = B9600;
			break ;
		default: 
			baudrate = B115200;
			break;
	}

	if(tcgetattr(fd, ttyold) != 0)
	{
		printf(" ERROR : tcgetattr \n");
		return -1;
	}

	ttynew = ttyold;
	cfsetospeed(ttynew, baudrate);
	cfsetispeed(ttynew, baudrate);
	ttynew -> c_cflag = ( ttynew -> c_cflag & ~CSIZE ) | CS8 ; // 8 data bits (8)
	ttynew -> c_cflag &= ~( PARENB | PARODD ); // no parity (N )
	ttynew -> c_cflag &= ~CSTOPB ;// 1 stop bit (1)

	ttynew -> c_cflag |= (CLOCAL | CREAD);         // ignore modem status lines , and
	ttynew -> c_cflag &= ~CRTSCTS;                 // no flow control
	ttynew -> c_iflag &= ~IGNBRK ;                  // disable break processing
	ttynew -> c_iflag &= ~( IXON | IXOFF | IXANY ); // shut off xon / xoff ctrl

	ttynew -> c_lflag = 0;
	ttynew -> c_oflag = 0;
	ttynew -> c_cc[VMIN] = 0;
	ttynew -> c_cc[VTIME] = 100;
	/*
	* TCSANOW : Make the change immediately .
	* TCSADRAIN : Make the change after all queued output has been written .
	* TCSAFLUSH : This is like TCSADRAIN , but also discards any queued input .
	*/
	if(tcsetattr(fd, TCSANOW, ttynew) != 0)
	{
		printf(" ERROR : tcsetattr \n" );
		return -1;
	}

	return 0;
}

char leer_serial()
{
	char dato;

	read(fd, &dato, sizeof(dato));

	return dato;
}

void imprimir_retardo(int borrar)
{
	if(borrar == 1)
	{
		const char* limpiar_delay_anterior = "\033[2K";
		const char* mover_cursor = "\033[1A";

		write(fd, limpiar_delay_anterior, strlen(limpiar_delay_anterior));
		retardo_fijo();
		write(fd, mover_cursor, strlen(mover_cursor));
	}
	
	char retardo[50];

	// esta funcion hace que el valor de tiempo de retardo se guarde en la cadena
	// para así poder mandarla por serial
	sprintf(retardo, "Delay: %d ms.\r\n", tiempo_retardo);
	
	// una vez tenemos la cadena formada, la mandamos por serial
	write(fd, retardo, strlen(retardo));
}

void limpiar_serial()
{
	const char* limpiar_pantalla = "\033[2J";
	const char* mover_cursor = "\033[H";
	
	write(fd, mover_cursor, strlen(mover_cursor));
	retardo_fijo();	// se pone un retardo porque se necesita que pase un tiempo entre limpiar la pantalla y mover el cursor
	write(fd, limpiar_pantalla, strlen(limpiar_pantalla));
}
