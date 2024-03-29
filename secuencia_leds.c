// librerías externas
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <wiringPi.h>

// archivos de cabecera propios
#include "secuencia_leds.h"
#include "setup.h"
#include "impresion_pantalla.h"
#include "modo_remoto.h"

int tiempo_retardo;

void retardo()
{
        int tiempo_anterior, tiempo_actual;

        // tomamos el tiempo actual, y actualizamos ambos valores
        tiempo_actual = millis();
        tiempo_anterior = tiempo_actual;

        // esperamos el tiempo de retardo ya seteado
        while(tiempo_actual < tiempo_anterior + tiempo_retardo)
        {
                tiempo_actual = millis();

                if(interrupcion())
                {
                        apagar_leds(TODOS);
			modo();
                }
        }
}

void auto_fantastico()
{
        while(TRUE)
        {
                // prendemos de izquierda a derecha
                for(int i = 0; i < N_LEDS; i++) 
                {
                        apagar_leds(TODOS);

                        digitalWrite(leds_pinout[i], HIGH);

                        retardo();
                }
                // prendemos de derecha a izquierda
                for(int i = 6; i >= 1; i--)     // arrancamos del 7mo led, porque el 8vo ya esta prendido
                {
                        apagar_leds(TODOS);

                        digitalWrite(leds_pinout[i], HIGH);

                        retardo();
                }
        }
}

void el_choque()
{
        int tabla_datos [7][N_LEDS] =   { {1, 0, 0, 0, 0, 0, 0, 1},
                                          {0, 1, 0, 0, 0, 0, 1, 0},
                                          {0, 0, 1, 0, 0, 1, 0, 0},
                                          {0, 0, 0, 1, 1, 0, 0, 0},
                                          {0, 0, 1, 0, 0, 1, 0, 0},
                                          {0, 1, 0, 0, 0, 0, 1, 0},
                                          {1, 0, 0, 0, 0, 0, 0, 1} };

        while(TRUE)
        {
                for(int i = 0; i < 7; i++)
                {
                        for(int j = 0; j < N_LEDS; j++)
                                digitalWrite(leds_pinout[j], tabla_datos[i][j]);

                        retardo();
                }
        }
}

void la_apilada()
{
        while(TRUE)
        {
                for(int i = 0; i < N_LEDS; i++)
                {
                        for(int j = 0; j < N_LEDS - i; j++)
                        {
                                apagar_leds(N_LEDS - i);

                                digitalWrite(leds_pinout[j], HIGH);

                                retardo();
                        }

                        parpadeo(i);
                }
        }
}

void parpadeo(int led)
{
        for(int i = 0; i < N_PARPADEOS; i++)
        {
                digitalWrite(leds_pinout[N_LEDS - led - 1], HIGH);
                retardo();
                digitalWrite(leds_pinout[N_LEDS - led - 1], LOW);
                retardo();
        }

        digitalWrite(leds_pinout[N_LEDS - led - 1], HIGH);
}

void la_carrera()
{
        int tabla_datos [18][N_LEDS] =  { {1, 0, 0, 0, 0, 0, 0, 0},
                                          {1, 0, 0, 0, 0, 0, 0, 0},
                                          {0, 1, 0, 0, 0, 0, 0, 0},
                                          {0, 1, 0, 0, 0, 0, 0, 0},
                                          {0, 0, 1, 0, 0, 0, 0, 0},
                                          {0, 0, 1, 0, 0, 0, 0, 0},
                                          {0, 0, 0, 1, 0, 0, 0, 0},
                                          {0, 0, 0, 1, 0, 0, 0, 0},
                                          {1, 0, 0, 0, 1, 0, 0, 0},
                                          {0, 1, 0, 0, 1, 0, 0, 0},
                                          {0, 0, 1, 0, 0, 1, 0, 0},
                                          {0, 0, 0, 1, 0, 1, 0, 0},
                                          {0, 0, 0, 0, 1, 0, 1, 0},
                                          {0, 0, 0, 0, 0, 1, 1, 0},
                                          {0, 0, 0, 0, 0, 0, 1, 1},
                                          {0, 0, 0, 0, 0, 0, 0, 1},
                                          {0, 0, 0, 0, 0, 0, 0, 0},
                                          {0, 0, 0, 0, 0, 0, 0, 0} };

        while(TRUE)
        {
                for(int i = 0; i < 18; i++)
                {
                        for(int j = 0; j < N_LEDS; j++)
                                digitalWrite(leds_pinout[j], tabla_datos[i][j]);

                        retardo();
                }
        }
}

void contador_binario()
{
        int * binario;

        while(TRUE)
        {
                for(int i = 0; i < 256; i++)
                {
                        binario = dec_to_bin(i);

                        // prendemos los leds segun el valor binario
                        for (int j = 0; j < N_LEDS; j++)
                                digitalWrite(leds_pinout[j], *(binario + j));

                        retardo();
                }
        }
}

int * dec_to_bin(int decimal)
{
        int num_invertido[N_LEDS] = {0};            // [N_LEDS] porque la cantidad de leds nos indican la cantidad de bits
        static int num_binario[N_LEDS] = {0};

        // convertimos de decimal a binario
        for(int i = 0; decimal > 0; i++){
                num_invertido[i] = decimal % 2;
                decimal /= 2;
        }

        // invertimos el orden de los bits
        for(int i = 0; i < 8; i++)
                num_binario[7 - i] = num_invertido[i];

        // devolvemos el puntero al primer valor del arreglo
        return num_binario;
}

void explosion()
{
        int tabla_datos [7][N_LEDS] =   { {1, 0, 0, 0, 0, 0, 0, 1},
                                          {1, 1, 0, 0, 0, 0, 1, 1},
                                          {1, 1, 1, 0, 0, 1, 1, 1},
                                          {1, 1, 1, 1, 1, 1, 1, 1},
                                          {0, 0, 0, 0, 0, 0, 0, 0},
                                          {1, 1, 1, 1, 1, 1, 1, 1},
                                          {0, 0, 0, 0, 0, 0, 0, 0} };

        while(TRUE)
        {
                for(int i = 0; i < 7; i++)
                {
                        for(int j = 0; j < N_LEDS; j++)
                                digitalWrite(leds_pinout[j], tabla_datos[i][j]);

                        retardo();
                }
        }
}

void random_led()
{
        int numero;

        srandom(time(NULL));    // sirve para generar un valor random cada vez que llamamos a random()

        while(TRUE)
        {
                numero = random() % N_LEDS;                     // % N_LEDS le da el rango entre 0 y 7

                if(digitalRead(leds_pinout[numero]) == 0)           // si el led esta apagado, lo prende
                        digitalWrite(leds_pinout[numero], HIGH);
                else                                            // si el led esta prendido, lo apaga
                        digitalWrite(leds_pinout[numero], LOW);

                retardo();
        }
}

void feliz_cumple()
{
				   //     sol la si do re mi fa sol
	int tabla_datos [25][N_LEDS] =  { {1, 0, 0, 0, 0, 0, 0, 0},
                                          {1, 0, 0, 0, 0, 0, 0, 0},
                                          {0, 1, 0, 0, 0, 0, 0, 0},
                                          {1, 0, 0, 0, 0, 0, 0, 0},
                                          {0, 0, 0, 1, 0, 0, 0, 0},
                                          {0, 0, 1, 0, 0, 0, 0, 0},
                                          {1, 0, 0, 0, 0, 0, 0, 0},
                                          {1, 0, 0, 0, 0, 0, 0, 0},
                                          {0, 1, 0, 0, 0, 0, 0, 0},
                                          {1, 0, 0, 0, 0, 0, 0, 0},
                                          {0, 0, 0, 0, 1, 0, 0, 0},
                                          {0, 0, 0, 1, 0, 0, 0, 0},
                                          {0, 0, 0, 1, 0, 0, 0, 0},
                                          {0, 0, 0, 0, 0, 1, 0, 0},
                                          {0, 0, 0, 0, 0, 0, 0, 1},
                                          {0, 0, 0, 0, 0, 1, 0, 0},
                                          {0, 0, 0, 1, 0, 0, 0, 0},
                                          {0, 0, 1, 0, 0, 0, 0, 0},
					  {0, 1, 0, 0, 0, 0, 0, 0},
	                                  {0, 0, 0, 0, 0, 0, 1, 0},
                                          {0, 0, 0, 0, 0, 0, 1, 0},
                                          {0, 0, 0, 0, 0, 1, 0, 0},
                                          {0, 0, 0, 1, 0, 0, 0, 0},
                                          {0, 0, 0, 0, 1, 0, 0, 0},
                                          {0, 0, 0, 1, 0, 0, 0, 0} };

        while(TRUE)
        {
                for(int i = 0; i < 25; i++)
                {
                        for(int j = 0; j < N_LEDS; j++)
                                digitalWrite(leds_pinout[j], tabla_datos[i][j]);

                        retardo();
                }
        }
}

void cambiar_delay()
{
	while(TRUE)
	{
		set_delay();
		
		move(5,0);      // nos movemos para luego limpiar en el lugar que queremos
                clrtobot();     // limpiamos todo lo que esta en la linea y abajo
                mvprintw(5, 0, "Nuevo delay: %d ms", tiempo_retardo);

		retardo();
	}
}

void apagar_leds(int NUM_LEDS)
{
        for(int i = 0; i < NUM_LEDS; i++)
                digitalWrite(leds_pinout[i], LOW);
}
