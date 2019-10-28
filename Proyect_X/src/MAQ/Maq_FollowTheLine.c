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

//Declaracion de estados
#define 	X11X	0
#define 	X10X	1
#define 	X01X	2
#define 	RESET	3
#define 	ALARMA	4
#define 	CONTROL 5

/*
#define		CRUCE			0
#define		NOCRUCE			1
#define		PRIMERCRUCE		2
#define		ESPERANDO		4
*/

#define 	MAQOFF		0
#define 	RESET2		1
#define 	PRIMERCRUCE	2
#define 	NOCRUCE		3



//Velocidad del Auto
#define		VELOCIDAD_FTL 80



//Interruptores de las maquinas de estado
uint8_t Flag_Control = 0;
uint8_t Flag_MFTL2 = 0;




/*
uint8_t Maq_FollowTheLine(void){
	static uint8_t estado = RESET;

	switch(estado){

		case RESET:
			ftl();
			//Tank_Forward(VELOCIDAD_FTL);
			if(IR_IZQ_OUT == 1 && IR_DER_OUT == 1)		//DETECTAN CRUCE
			{
				ftl();
				estado = PRIMERCRUCE;
			}
			else
			{
				ftl();
				estado = NOCRUCE;
			}

			break;

		case PRIMERCRUCE:
			if(IR_IZQ_OUT == 0 && IR_DER_OUT == 0)
			{
				estado = NOCRUCE;
				ftl();
			}
			if(IR_IZQ_OUT == 1 && IR_DER_OUT == 1)
			{
				ftl();
				estado = ESPERANDO;

			}
			else
			{
				estado = ESPERANDO;
				ftl();
			}
			break;

		case NOCRUCE:

			if(IR_IZQ_OUT == 1 && IR_DER_OUT == 1)
			{		//DETECTAN CRUCE
				Tank_Brake();
				Tank_Backward(VELOCIDAD_FTL);
				TimerStart(1, 1, TimerFrenar, DEC); // Timer para hacer que valla para atras 1 decima de segundo (y luego frena). Para que frene en el lugar
				estado = RESET;
				return EXITO;
			}
			else
			{
				estado = NOCRUCE;
				ftl();
			}
			break;

		case ESPERANDO:

			if(IR_IZQ_OUT == 1 && IR_DER_OUT == 1)
			{
				ftl();
				estado = ESPERANDO;
			}
			else
			{
				estado = NOCRUCE;
				ftl();
			}


		default: estado = RESET;
	}
	return ENPROCESO;
}
*/

uint8_t Maq_FollowTheLine_v2(void)
{
	static uint8_t estado2 = MAQOFF;
	static uint8_t cruce = 0; //sirve para saber si arrancaste en un cruce
							  // 0 = arranco en cruce
							  // 1 = ya salio del primer cruce | no arranco en cruce


	switch(estado2)
	{
		case MAQOFF:
			if(Flag_MFTL2 == ON)
				estado2 = RESET2;

			else
				estado2 = MAQOFF;
			break;

		case RESET2:

			if(IR_IZQ_OUT == 1 && IR_DER_OUT == 1)
			{
				Flag_Control = ON;
				cruce = 0;
				estado2 = PRIMERCRUCE;
			}

			if(IR_IZQ_OUT == 0 && IR_DER_OUT == 0)
			{
				Flag_Control = ON;
				cruce = 1;
				estado2 = NOCRUCE;
			}
			if(Flag_MFTL2 == 0)
			{
				estado2 = MAQOFF;
			}
			break;

		case PRIMERCRUCE:
			if(cruce == 0)
			{
				Flag_Control = ON;
				estado2 = PRIMERCRUCE;
			}

			if(IR_IZQ_OUT == 0 && IR_DER_OUT == 0)
			{
				Flag_Control = ON;
				cruce = 1;
				estado2 = NOCRUCE;
			}
			if(Flag_MFTL2 == 0)
			{
				estado2 = MAQOFF;
			}
			break;

		case NOCRUCE:
			if(cruce == 1)
			{
				Flag_Control = ON;
				estado2 = NOCRUCE;
			}

			if(IR_IZQ_OUT == 1 && IR_DER_OUT == 1)
			{
				//ESTE ESTADO ES EL QUE NO ANDA
				Tank_Brake();
				Tank_Backward(VELOCIDAD_FTL); //hago que vaya 1 decima de segundo para atras para que frene en el lugar
				//ESTE TIMER
				TimerStart(1, 1, TimerFrenar, DEC); //Por lo que estuve probando, nunca interrumpe. Sige indefinidamente para atras
				cruce = 0;
				estado2 = MAQOFF;
				Flag_Control = OFF;
				Flag_MFTL2 = OFF;
				estado2 = MAQOFF;
				//Tank_Coast();

				return EXITO;
			}

			if(Flag_MFTL2 == 0)
			{
				estado2 = MAQOFF;
			}
			break;

		default:
			estado2 = MAQOFF;
			break;
	}
	return ENPROCESO;
}


uint8_t ftl(void)	//se encarga del interior
{
	static uint8_t estado = CONTROL;

	switch(estado)
	{
		case CONTROL:

			if(Flag_Control == 1)
			{
				estado = RESET;
			}
			else
			{
				estado = CONTROL;
				Tank_Brake();
			}
			break;

		case RESET:

			Tank_Forward(VELOCIDAD_FTL);
				estado = X11X;

			if(Flag_Control == 0)
			{
				estado = CONTROL;
				Tank_Brake();
			}

			break;

		case X11X:

			if(IR_IZQ_IN == 0 && IR_DER_IN == 1)
			{
				Tank_Right(VELOCIDAD_FTL);
				estado = X01X;
			}

			if(IR_IZQ_IN == 1 && IR_DER_IN == 0)
			{
				Tank_Left(VELOCIDAD_FTL);
				estado = X10X;
			}
			if(Flag_Control == 0)
			{
				estado = CONTROL;
				Tank_Brake();
			}

			break;

		case X10X:

			if(IR_IZQ_IN == 1 && IR_DER_IN == 1)
			{
				Tank_Forward(VELOCIDAD_FTL);
				estado = X11X;

			}

			if(Flag_Control == 0)
			{
				estado = CONTROL;
				Tank_Brake();
			}

			break;

		case X01X:

			if(IR_IZQ_IN == 1 && IR_DER_IN == 1)
			{
				Tank_Forward(VELOCIDAD_FTL);
				estado = X11X;

			}
			if(Flag_Control == 0)
			{
				estado = CONTROL;
				Tank_Brake();
			}

			break;

		case ALARMA:

			return FALLO;
			break;

		default: estado = CONTROL;
		}
		return ENPROCESO;
}


void TimerFrenar(void)
{
	Tank_Coast();
	//Tank_Brake();



}



//Funciones asociadas a los eventos


//Funciones asociadas a los eventos


//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
//------------------------------FIN MAQUINA DE ESTADOS DE FOLLOW THE LINE---------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------


