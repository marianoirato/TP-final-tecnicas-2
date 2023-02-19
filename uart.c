#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringSerial.h>

int main ()
{
	unsigned char string;
	int UART, select = -1, check;
	
	wiringPiSetup ();
	
	UART = serialOpen("/dev/ttyS0", 9600);

	if (UART == -1)
	{
		printf("\n Conexion fallida.\n");
		return -1;
	}
	else
	{
		while (select != 3)
		{
			printf("-----------\n"
			"1. Enviar\n"
			"2. Recibir\n"
			"3. Salir\n"
			"-----------\n");
			scanf("%d", &select);
			
			string = 'a';		
	
			switch (select)
			{
				case 1:
					while(string != '0')
					{
						printf("\nDatos a trasmitir: ");
						string = getchar();
						
						if(string != 10)
						{
							serialPutchar(UART, string);
							printf("\nDato trasmitido: %d\n", string);
						}
						
						serialPutchar(UART, '\r');
						serialPutchar(UART, '\n');
					}
					break;
			
				case 2:
					while(string != '0')
					{
						string = serialGetchar(UART);
						printf ("\nDato recibido: %c\n", string);
					}
					break;
			}
		}
	}
	
	serialClose(UART);
	
	return 0;
}

