#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "setup.h"
#include "impresion_pantalla.h"
#include "secuencia_leds.h"
#include "modo_remoto.h"

#define SALIR 115		// tecla 's'

int opcion = 0;                     // secuencia de leds elegida
int modo_elegido;
int elegir_modo = 1;

void modo()
{
	if(elegir_modo)
	{
		printf("\nElija el modo a utilizar: \n");
		printf("0: Modo remoto.\n");
		printf("1: Modo local.\n");

		printf("Pulse cualquier otra tecla numérica para salir. \n");

		// aceptamos solamente números
		while(scanf("%d", &modo_elegido) != 1)        // si el scanf recibe un caracter, va a devolver algo distinto de 1
		{
			printf("Ingrese un número: ");
			while(getchar() != '\n');       // este while es para que el printf no se imprima indefinidamente
		}   

		elegir_modo = 0;
	}

	switch(modo_elegido)
	{
		case 0:
			modo_remoto();
			break;
		case 1:
			modo_local();
			break;
		default:
			exit(0);
			break;
	}
}

void modo_local()
{
        printf("\nElija una secuencia de leds: \n");
        printf("1: El auto Fantástico. \n");
        printf("2: El Choque. \n");
        printf("3: La Apilada. \n");
        printf("4: La Carrera. \n");
        printf("5: Contador binario. \n");
        printf("6: Explosion. \n");
        printf("7: Random LED. \n");
        printf("8: Feliz cumpleaños. \n");
       	printf("9: Setear delay. \n");

	printf("Pulse cualquier otra tecla numérica para salir. \n");
 	
	// aceptamos solamente números
	while(scanf("%d", &opcion) != 1)	// si el scanf recibe un caracter, va a devolver algo distinto de 1
	{
		printf("Ingrese un número: ");
		while(getchar() != '\n');	// este while es para que el printf no se imprima indefinidamente
	}					// se imprime 1 vez por cada \n (enter)

        switch(opcion)
        {
                case 1:
                        crear_ventana();
                        auto_fantastico();
                        break;
                case 2:
                        crear_ventana();
                        el_choque();
                        break;
                case 3:
                        crear_ventana();
                        la_apilada();
                        break;
                case 4:
                        crear_ventana();
                        la_carrera();
                        break;
                case 5:
                        crear_ventana();
                        contador_binario();
                        break;
                case 6:
                        crear_ventana();
                        explosion();
                        break;
                case 7:
                        crear_ventana();
                        random_led();
                	break;
		case 8:
                        crear_ventana();
                        feliz_cumple();
			break;
		case 9:
			crear_ventana();
			cambiar_delay();
			break;
		default:
                        elegir_modo = 1;
			modo();	
                        break;	  
	}
}

void crear_ventana()
{
        WINDOW *win;

        win = initscr();        // creamos la ventana

        nodelay(win, TRUE);     // esta funcion, hace que el getch no sea bloqueante
        noecho();               // no imprime el caracter ingresado por teclado

        keypad(stdscr, TRUE);   // agrega las flechas

        clear();

        mvprintw(0, 0, "Entraste a modo: ");

        switch(opcion)
        {
                case 1:
                        mvprintw(0, 17, "Auto fantástico.");
                        break;
                case 2:
                        mvprintw(0, 17, "El choque.");
                        break;
                case 3:
                        mvprintw(0, 17, "La apilada.");
                        break;
                case 4:
                        mvprintw(0, 17, "La carrera.");
                        break;
                case 5:
                        mvprintw(0, 17, "Contador binario.");
                        break;
                case 6:
                        mvprintw(0, 17, "Explosion.");
                        break;
                case 7:
                        mvprintw(0, 17, "Random LED.");
                        break;
		case 8:
                        mvprintw(0, 17, "Feliz cumpleaños.");
                        break;
		case 9: 
			mvprintw(0, 17, "Setear delay.");
			break;
		default:
                        break;
        }
      
	if(opcion != 9)
	{
		mvprintw(2, 0, "Pulse la flecha hacia arriba para aumentar la velocidad (-100 ms), y la fecha hacia abajo para disminuirla (+100 ms). \n");
       		mvprintw(3, 0, "Pulse la tecla 's' para salir. \n\n");
		// enviamos un 0 a variacio_velocidad, es decir, no varia la velocidad, por lo tanto, devuelve el delay actual
		mvprintw(5, 0, "-Delay inicial: %d ms", variacion_velocidad(0)); 
	}
	else
	{
		mvprintw(2, 0, "Ajuste el potenciometro para cambiar el delay. \n");
		mvprintw(3, 0, "Pulse la tecla 's' para salir. \n\n");
	}
}

// en caso de que haya interrupcion se devuelve un 1
int interrupcion()
{
	int tecla, retraso, retraso_anterior;

	// modo local
        if(modo_elegido)
	{
		tecla = getch();

		switch(tecla)
		{
			case KEY_UP:
				retraso_anterior = variacion_velocidad(0); // lo hacemos para ver si el valor ya está en 100 ms, así no se impirme que se aumentó la velocidad
				retraso = variacion_velocidad(2);
				if(retraso != retraso_anterior)
				{
					move(6,0);      // nos movemos para luego limpiar en el lugar que queremos
					clrtobot();     // limpiamos todo lo que esta en la linea y abajo
					mvprintw(6, 0, "-Aumentó la velocidad 100 ms.");
					mvprintw(7, 0, "-Retraso: %d ms", retraso);
				}
				break;
			case KEY_DOWN:
				retraso = variacion_velocidad(1);
				move(6,0);      // nos movemos para luego limpiar en el lugar que queremos
				clrtobot();     // limpiamos todo lo que esta en la linea y abajo
				mvprintw(6, 0, "-Disminuyó la velocidad 100 ms.");
				mvprintw(7, 0, "-Retraso: %d ms", retraso);
				break;
			case SALIR:
				endwin();       // cerramos la ventana creada en crear_ventana()
				return 1;
				break;

			default:
				return 0;
		}
	}
	// modo remoto
	else
	{
		tecla = leer_serial();

		switch(tecla)
		{
			case SALIR:
				return 1;
				break;
			case '[':
				retraso = variacion_velocidad(1);
				break;
		}
	}

        return 0;
}

