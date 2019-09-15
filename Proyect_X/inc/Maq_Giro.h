/**
*	\file funciones.h
*	\brief Resumen del archivo
*	\details Descripcion detallada del archivo
*	\author CrisafienGerman
*	\date 15-09-2019 18:56:46
*/
#include "DR_tipos.h"
//Declaracion de constantes
#define TRUE  1
#define FALSE  0

#define ENPROCESO 0
#define EXITO 1



//declaracion de la maquina
uint8_t Maq_Giro(uint8_t orient);


//Declaracion de estados
#define 	IZQUIERDA	0
#define 	RESET	1
#define 	DERECHA	2
#define 	CUARENTAYCINCOGRADOS	3

//Prototipos de los eventos
int esIzquierda(void);
int esDerecha(void);

//Prototipos de las acciones
void Frenar(void);
void FIzquierda(void);
void FDerecha(void);
