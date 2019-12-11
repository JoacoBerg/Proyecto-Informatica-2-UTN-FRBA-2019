/**
*	\file funciones.h
*	\brief Resumen del archivo
*	\details Descripcion detallada del archivo
*	\author Tanks
*	\date 15-09-2019 18:56:46
*/
#include <DR_tipos.h>
//Declaracion de constantes
#define 	TRUE  		1
#define 	FALSE  		0
#define 	IZQ			0
#define 	DER			1



//declaracion de la maquina
uint8_t Maq_Giro(uint8_t orient);
uint8_t Maq_Giro_v2(uint8_t orient);

extern uint8_t Flag_Control_G;

//Prototipos de los eventos
int esIzquierda(void);
int esDerecha(void);

//Prototipos de las acciones
void Frenar(void);
void FIzquierda(void);
void FDerecha(void);
