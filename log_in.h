#ifndef _LOG_IN_H
#define _LOG_IN_H

typedef struct{
	char * username;
        char * password;
}usuarios;

#define CANTIDAD_USUARIOS 4
#define NAME_LENGTH 8
#define TAM_MAX_CONTRASEÑA 7
#define N_INTENTOS 3

int log_in();
usuarios * crear_usuarios();
char * ingrese_usuario();
char * ingrese_contraseña(int);

#endif


