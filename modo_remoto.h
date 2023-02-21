#ifndef _MODO_REMOTO_H
#define _MODO_REMOTO_H

extern int fd; // descriptor de archivo del puerto serie
extern struct termios ttyold, ttynew;

void modo_remoto();
int termset(int fd, int baudrate, struct termios *ttyold, struct termios *ttynew);
char leer_serial();


#endif

