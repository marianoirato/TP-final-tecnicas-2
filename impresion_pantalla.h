#ifndef _IMPRESION_PANTALLA_H
#define _IMPRESION_PANTALLA_H

void crear_ventana();
int interrupcion();
void modo_local();
void modo();
int comprobar_modo();

extern int opcion;                     // secuencia de leds elegida
extern int modo_elegido;
extern int elegir_modo;


#endif
