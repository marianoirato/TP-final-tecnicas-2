#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wiringPi.h>
#include "secuencia_leds.h"
#include "setup.h"
#include "impresion_pantalla.h"

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
                        menu();
                }
        }
}

int variacion_velocidad(int var)
{
        // cuando se apreta la flecha hacia arriba, el delay disminuye (aumenta la velocidad)
        if(var == 2 && tiempo_retardo >= 200)
                tiempo_retardo -= 100;

        // cuando se apreta la flecha hacia abajo, el delay aumenta (disminuye la velocidad)
        if(var == 1)
                tiempo_retardo += 100;

        // devolvemos el tiempo para poder imprimirlo en pantalla
        return tiempo_retardo;
}

void auto_fantastico()
{
        while(TRUE)
        {
                // prendemos de izquierda a derecha
                for(int i = 1; i < N_LEDS; i++) // arrancamos del 2do led, porque el 1ro queda prendido en el bucle siguiente
                {
                        apagar_leds(TODOS);

                        digitalWrite(pinouts[i], HIGH);

                        retardo();
                }
                // prendemos de derecha a izquierda
                for(int i = 6; i >= 0; i--)     // arrancamos del 7mo led, porque el 8vo ya esta prendido
                {
                        apagar_leds(TODOS);

                        digitalWrite(pinouts[i], HIGH);

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
                                digitalWrite(pinouts[j], tabla_datos[i][j]);

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

                                digitalWrite(pinouts[j], HIGH);

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
                digitalWrite(pinouts[N_LEDS - led - 1], HIGH);
                retardo();
                digitalWrite(pinouts[N_LEDS - led - 1], LOW);
                retardo();
        }

        digitalWrite(pinouts[N_LEDS - led - 1], HIGH);
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
                                digitalWrite(pinouts[j], tabla_datos[i][j]);

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
                                digitalWrite(pinouts[j], *(binario + j));

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
                                digitalWrite(pinouts[j], tabla_datos[i][j]);

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

                if(digitalRead(pinouts[numero]) == 0)           // si el led esta apagado, lo prende
                        digitalWrite(pinouts[numero], HIGH);
                else                                            // si el led esta prendido, lo apaga
                        digitalWrite(pinouts[numero], LOW);

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
                                digitalWrite(pinouts[j], tabla_datos[i][j]);

                        retardo();
                }
        }
}

void apagar_leds(int NUM_LEDS)
{
        for(int i = 0; i < NUM_LEDS; i++)
                digitalWrite(pinouts[i], LOW);
}
