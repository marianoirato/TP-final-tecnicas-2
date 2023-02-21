#ifndef _SECUENCIA_LEDS_H
#define _SECUENCIA_LEDS_H

void setup();
void retardo();
extern int variacion_velocidad(int, int);
int* dec_to_bin(int);

// secuencias de leds
void auto_fantastico();
void el_choque();
void la_apilada();
void parpadeo(int);
void la_carrera();
void contador_binario();
void explosion();
void random_led();
void feliz_cumple();

void cambiar_delay();

void apagar_leds(int);

#define N_LEDS 8
#define N_PARPADEOS 3
#define TODOS 8

extern int tiempo_retardo;

#endif
