.text
.arm
.global variacion_velocidad

// R0 indica si aumentamos o disminuimos el delay
// R1 es tiempo_retardo

variacion_velocidad:

	CMP R0,#2
	BEQ caso1
	CMP R0,#1
	BEQ caso2
	B default

// cuando se apreta la flecha hacia arriba, el delay disminuye (aumenta la velocidad)
caso1:  CMP R1,#200		
	SUBGE R0,R1,#100
	BLT default
	B salir

// cuando se apreta la flecha hacia abajo, el delay aumenta (disminuye la velocidad)
caso2:  ADD R0,R1,#100		
	B salir

// en otro caso, devolvemos tiempo_retardo
default:
	MOV R0,R1

salir:
	MOV PC,LR
