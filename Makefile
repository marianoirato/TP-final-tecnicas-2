CC = gcc
AS = as
LD = ld

OBJECTS = main.o setup.o log_in.o secuencia_leds.o impresion_pantalla.o

CFLAGS = -Wall -g -c
ASFLAGS = -g
LDFLAGS = -g

# creamos los archivos .o y los compilamos todos juntos en main

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

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean:
	rm *.o
