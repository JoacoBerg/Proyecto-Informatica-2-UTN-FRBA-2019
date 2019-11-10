/*******************************************************************************************************************************//**
 *
 * @file		Maq_Follow_the_line.c
 * @brief		Descripcion del modulo
 * @date		15 sep. 2019
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <DR_IR.h>
#include <Maq_FollowTheLine.h>
#include "Tanks.h"
#include "DR_tipos.h"
#include "PR_Entradas.h"
#include "PR_Timers.h"

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/


//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
//------------------------------MAQUINA DE ESTADOS DE FOLLOW THE LINE---------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------

//Declaracion de estados de ftl()
#define 	X01X	1
#define 	X10X	2
#define 	X11X	3
#define 	RESET	0
#define 	ALARMA	4
#define 	CONTROL 5

//Declaracion de estados de Maq_FollowTheLine_v2()
#define 	RESET2		0
#define 	PRIMERCRUCE	1
#define 	NOCRUCE		2
#define 	WAITING		3



//Velocidad del Auto
#define		VELOCIDAD_FTL 80
#define		TIMER1 1
#define		TIMER4 4


//Flags de las maquinas de estado
uint8_t Flag_Turn_ftl = OFF;
uint8_t waiting_IRs = OFF;
uint8_t waiting_freno = OFF;

//Variable de estado de Switch

void TimerFrenar(void);
void TimerSleepIRs(void);

//Maquina que detecta cruces y llama a ftl()
uint8_t Maq_FollowTheLine_v2(void)
{
	static uint8_t estado2 = RESET2;
	switch(estado2)
	{
		case RESET2:

			Flag_Turn_ftl = ON;
			waiting_IRs = OFF;// para que no entre a ningun if de WAITING
			TimerStart(TIMER4, 4, TimerSleepIRs, DEC);
			estado2 = WAITING;
			break;

		case NOCRUCE:

			if(IR_IZQ_OUT == ON && IR_DER_OUT == ON){
				estado2 = RESET2;
				return EXITO;
			}
			break;

		case WAITING:

			if(waiting_IRs == ON)
				estado2 = NOCRUCE;
			break;

		default:

			estado2 = RESET2;
			break;
	}
	return ENPROCESO;
}

//Funcion de Handler de Timer4
void TimerSleepIRs(void){
	waiting_IRs = ON;
}

//Funcion de Handler de Timer1
void TimerFrenar(void){
	Tank_Brake();
	waiting_freno = ON;
}

uint8_t Maq_Freno(void){
	static uint8_t estado = RESET;
	switch(estado)
	{

		case RESET:

			Flag_Turn_ftl = OFF;
			Tank_Brake();
			Tank_Backward(VELOCIDAD_FTL);
			TimerStart(TIMER1, 1, TimerFrenar, DEC); //hago que vaya 1 decima de segundo para atras para que frene en el lugar
			waiting_freno = OFF;
			estado = WAITING;
			break;

		case WAITING:

			if(waiting_freno == ON){
				waiting_freno = OFF;
				estado = RESET;
				return EXITO;
			}
			break;

		default:

			estado = RESET;
			break;

	}
	return ENPROCESO;
}

//Este es el codigo seguidor de lineas (solo utiliza IR del medio)
uint8_t ftl(void)	//se encarga del interior
{
	static uint8_t estado = CONTROL;

	switch(estado)
	{
		case CONTROL:

			if(Flag_Turn_ftl == ON)
			{
				estado = RESET;
			}
			else
			{
				estado = CONTROL;
			}
			break;

		case RESET:

			Tank_Forward(VELOCIDAD_FTL);
				estado = X11X;

			if(Flag_Turn_ftl == OFF)
			{
				estado = CONTROL;
			}

			break;

		case X11X:

			if(IR_IZQ_IN == OFF && IR_DER_IN == ON)
			{
				Tank_Right(VELOCIDAD_FTL);
				estado = X01X;
			}

			if(IR_IZQ_IN == ON && IR_DER_IN == OFF)
			{
				Tank_Left(VELOCIDAD_FTL);
				estado = X10X;
			}
			if(Flag_Turn_ftl == OFF)
			{
				estado = CONTROL;
			}

			break;

		case X10X:

			if(IR_IZQ_IN == ON && IR_DER_IN == ON)
			{
				Tank_Forward(VELOCIDAD_FTL);
				estado = X11X;

			}

			if(Flag_Turn_ftl == OFF)
			{
				estado = CONTROL;
			}

			break;

		case X01X:

			if(IR_IZQ_IN == ON && IR_DER_IN == ON)
			{
				Tank_Forward(VELOCIDAD_FTL);
				estado = X11X;

			}
			if(Flag_Turn_ftl == OFF)
			{
				estado = CONTROL;
			}

			break;

		case ALARMA:

			return FALLO;
			break;

		default: estado = CONTROL;
		}
		return ENPROCESO;
}





//Funciones asociadas a los eventos


//Funciones asociadas a los eventos


//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
//------------------------------FIN MAQUINA DE ESTADOS DE FOLLOW THE LINE---------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------


