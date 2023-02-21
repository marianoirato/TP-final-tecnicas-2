#include <stdio.h>

extern int variacion_velocidad(int a, int tiempo_retardo);

int main(void)
{
	int a = 1;
	int tiempo_retardo = 200;

	tiempo_retardo = variacion_velocidad(a, tiempo_retardo);

	printf("Tiempo retardo: %d \n", tiempo_retardo);

	return 0;
}




