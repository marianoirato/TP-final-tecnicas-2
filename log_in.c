// librerías externas
#include <stdio.h>
#include <termios.h>
#include <string.h>

// archivos de cabecera propios
#include "log_in.h"

#define FD_STDIN 0

int log_in()
{
	int intentos = 0;

	usuarios * usuario = crear_usuarios();	// creamos la estructura usuario

	// se repite hasta que no haya mas intentos
        while(intentos < N_INTENTOS)
	{
		char * nombre_usuario = ingrese_usuario();	// guardamos el nombre ingresado por teclado
		char * contraseña;				// guardamos la contraseña ingresada por teclado
		int tamaño_contraseña = 0;

        	for(int i = 0; i < CANTIDAD_USUARIOS; i++)
        	{
			// si el usuario se ingresa correctamente, nos pide la contraseña
			if(strcmp((usuario + i)->username, nombre_usuario) == 0)
                	{
				tamaño_contraseña = strlen((usuario + i)->password);

				contraseña = ingrese_contraseña(tamaño_contraseña);

				// si la contraseña se ingresa correctamente, entonces devolvemos un 1
				// indicando que ingresamos al sistema
				if(strcmp((usuario + i)->password, contraseña) == 0)
				{
					printf("\nBienvenido al sistema. \n");

					return 1;
				}
			}
			// la primer condición es para que se imprima 1 sola vez, y no las N veces del loop
			// la segunda condición, nos dice que no se ingresó correctamente el usuario, pero
			// igual nos pide la contraseña, simulando cualquier programa en la vida real, donde
			// te indica que está mal una vez ingresado ambos parámetros
			else if(i == CANTIDAD_USUARIOS - 1 && *contraseña == '\0')
				contraseña = ingrese_contraseña(TAM_MAX_CONTRASEÑA);
		}

		intentos++;

		printf("Nombre de usuario o contraseña incorrecto. Le quedan %d intentos.\n", N_INTENTOS - intentos);
	}

	printf("Ingresó incorrectamente la contraseña o el usuario %d veces. \n", N_INTENTOS);

        return 0;
}

usuarios * crear_usuarios()
{
        static usuarios usuario[CANTIDAD_USUARIOS];

        usuario[0].username = "Facundo";
        usuario[0].password = "Facundo";

        usuario[1].username = "Mariano";
        usuario[1].password = "Mariano";

        usuario[2].username = "Tomas";
        usuario[2].password = "Tomas";

        usuario[3].username = "Uriel";
        usuario[3].password = "Uriel";

        return usuario;
}

char * ingrese_usuario()
{
        static char nombre_usuario[NAME_LENGTH];

        printf("Ingrese su usuario: ");
        scanf("%s", nombre_usuario);

	return nombre_usuario;
}

char * ingrese_contraseña(int tamaño_contraseña)
{
        // setup de la terminal para utilizar modo no canónico
        struct termios t_old, t_new;
        tcgetattr(FD_STDIN, &t_old);		// lee atributos del teclado
        t_new = t_old;
        t_new.c_lflag &= ~(ECHO | ICANON);	// anula entrada canónica y eco
        tcsetattr(FD_STDIN,TCSANOW,&t_new);	// actualiza con los valores nuevos de la config. TCSANOW = activar la modificación inmediatamente

        // variables
	static char contraseña[TAM_MAX_CONTRASEÑA] = {'\0'};      

	// igualamos la contraseña a 0
	for(int i = 0; i < TAM_MAX_CONTRASEÑA; i++)
		*(contraseña + i) = '\0';

	printf("Ingrese su conraseña: ");

        for(int i = 0; i < tamaño_contraseña; i++)
	{
                contraseña[i] = getchar();

                if(contraseña[i] == 127 && i > 0)
                {
			printf("\b \b");
                        i -= 2;
                }
                else if(contraseña[i] != 127 && contraseña[i] != 10)   //  no mostrar * si se presiona delete o enter
                        printf("*");
                else
                        i--;
	}

        printf("\n");
        
	tcsetattr(FD_STDIN, TCSANOW, &t_old); // actualiza con los valores previos

	return contraseña;
}
