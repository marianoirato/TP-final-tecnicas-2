// librerías externas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <fcntl.h>
#include <termios.h>

// archivos de cabecera propios
#include "modo_remoto.h"
#include "impresion_pantalla.h"
#include "secuencia_leds.h"

int fd;	// file descriptor

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

	tcflush(fd, TCIOFLUSH);	// limpia lo que se encuentra en el buffer

	write(fd, texto_menu, sizeof(texto_menu));

	tcdrain(fd);	// esta función espera hasta que se escribe toda la información

	// esperamos hasta que se ingrese un número entre 0 y 8
	do
		read(fd, &opcion_remoto, sizeof(opcion_remoto));
	while(!(opcion_remoto >= '0' && opcion_remoto <= '8'));
	
	switch(opcion_remoto)
	{
		// las ' ' se ponen porque el serial nos devuleve un char, no un int
		case '1':
			write(fd, "Ingresaste al modo ", 19);
			write(fd, "Auto Fantastico.\r\n", 18);
			write(fd, "Ingrese la tecla 's' para salir.\r\n", 34);
			write(fd, "Ingrese la tecla 'p' para aumentar la velocidad o la tecla 'l' para disminuirla.\r\n", 82);		
			imprimir_retardo(0);	// se envía un 0 porque es la primera vez que se imprime el retardo, no queremos que lo borre
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
			elegir_modo = 1;	// si salimos del modo, queremos que nos vuelva a preguntar que modo queremos utilizar
			close(fd);
			modo();
			break;
	}

        close(fd);
}

// configuramos la comunicación serial
int termset(int fd, int baudrate, struct termios *ttyold, struct termios *ttynew)
{
	// elegimos el baudrate
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

	// copiamos los atributos de la terminal en ttyold
	if(tcgetattr(fd, ttyold) != 0)
	{
		printf(" ERROR : tcgetattr \n");
		return -1;
	}

	// copiamos los atributos en la nueva terminal
	ttynew = ttyold;
	// modificamos la nueva terminal
	cfsetospeed(ttynew, baudrate);					// seteamos el baudrate del output
	cfsetispeed(ttynew, baudrate);					// seteamos el baudrate del input
	ttynew -> c_cflag = ( ttynew -> c_cflag & ~CSIZE ) | CS8 ;	// 8 data bits (8)
	ttynew -> c_cflag &= ~( PARENB | PARODD );			// sin paridad (N)
	ttynew -> c_cflag &= ~CSTOPB ;					// 1 bit de parada (1)

	ttynew -> c_cflag |= (CLOCAL | CREAD);          // ignoramos señales DTR y DSR
	ttynew -> c_cflag &= ~CRTSCTS;                  // desactiva RTS/CTS
	ttynew -> c_iflag &= ~IGNBRK ;                  // desactiva la señal de break, esta señal se utiliza para interrupciones momentaneas
	ttynew -> c_iflag &= ~( IXON | IXOFF | IXANY ); // shut off xon / xoff ctrl

	ttynew -> c_lflag = 0;
	ttynew -> c_oflag = 0;
	ttynew -> c_cc[VMIN] = 0;			// setea número mínimo de carácteres a leer por la función read()
	ttynew -> c_cc[VTIME] = 100;			// setea el tiempo a esperar por información antes de volver de la función read()
	
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
		// estos caracteres nos permiten limpiar la terminal serial
		const char* limpiar_delay_anterior = "\033[2K";
		const char* mover_cursor = "\033[1A";

		write(fd, limpiar_delay_anterior, strlen(limpiar_delay_anterior));
		tcdrain(fd);	// esta función espera hasta que se escribe toda la información
		write(fd, mover_cursor, strlen(mover_cursor));
	}
	
	char retardo[50];

	// esta función hace que el valor de tiempo de retardo se guarde en la cadena
	// para así poder mandarla por serial
	sprintf(retardo, "Delay: %d ms.\r\n", tiempo_retardo);
	
	// una vez tenemos la cadena formada, la mandamos por serial
	write(fd, retardo, strlen(retardo));
}

void limpiar_serial()
{
	// estos caracteres nos permiten limpiar la terminal serial
	const char* limpiar_pantalla = "\033[2J";
	const char* mover_cursor = "\033[H";
	
	write(fd, mover_cursor, strlen(mover_cursor));
	tcdrain(fd);	// esta función espera hasta que se escribe toda la información
	write(fd, limpiar_pantalla, strlen(limpiar_pantalla));
}
