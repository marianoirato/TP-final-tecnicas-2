CC = gcc
AS = as

OBJECTS = main.o setup.o log_in.o secuencia_leds.o impresion_pantalla.o modo_remoto.o variacion_velocidad.o

CFLAGS = -Wall -g -c
ASFLAGS = -Wall -g  

# creamos los archivos .o y los compilamos todos juntos en main
# una vez compilados, se borran los .o

main:	$(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o main -lwiringPi -lcurses

setup.o: setup.c
	$(CC) $(CFLAGS) setup.c
	
log_in.o: log_in.c
	$(CC) $(CFLAGS) log_in.c

secuencia_leds.o: secuencia_leds.c
	$(CC) $(CFLAGS) secuencia_leds.c

impresion_pantalla.o: impresion_pantalla.c
	$(CC) $(CFLAGS) impresion_pantalla.c

modo_remoto.o: modo_remoto.c
	$(CC) $(CFLAGS) modo_remoto.c

variacion_velocidad.o: variacion_velocidad.s
	$(AS) $(ASFLAGS) variacion_velocidad.s -o variacion_velocidad.o

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean:
	rm *.o
