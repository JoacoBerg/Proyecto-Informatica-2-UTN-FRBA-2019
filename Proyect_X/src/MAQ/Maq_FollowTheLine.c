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
#define 	X11X	0
#define 	X10X	1
#define 	X01X	2
#define 	RESET	3
#define 	ALARMA	4
#define 	CONTROL 5

//Declaracion de estados de Maq_FollowTheLine_v2()
#define 	RESET2		0
#define 	PRIMERCRUCE	1
#define 	NOCRUCE		2
#define 	WAITING		3



//Velocidad del Auto
#define		VELOCIDAD_FTL 80



//Interruptores de las maquinas de estado
uint8_t Flag_Turn_ftl = 0;
uint8_t waiting = 0;
uint8_t estado2 = RESET2;




//Maquina que detecta cruces y llama a ftl()
uint8_t Maq_FollowTheLine_v2(void)
{
	switch(estado2)
	{
		case RESET2:

			Flag_Turn_ftl = ON;
			waiting = 0;// para que no entre a ningun if de WAITING
			TimerStart(4, 7, TimerSleepIRs, DEC);
			estado2 = WAITING;
			break;

		case NOCRUCE:

			if(IR_IZQ_OUT == 1 && IR_DER_OUT == 1){
				Flag_Turn_ftl = OFF;
				Tank_Brake();
				Tank_Backward(VELOCIDAD_FTL);
				TimerStart(1, 1, TimerFrenar, DEC); //hago que vaya 1 decima de segundo para atras para que frene en el lugar
				waiting = 0;
				estado2 = WAITING;
			}
			break;

		case WAITING:

			if(waiting == 1){
				estado2 = RESET2;
				return EXITO;
			}
			else if(waiting == 2){
				estado2 = NOCRUCE;
			}
			break;

		default:
			estado2 = RESET2;
			break;
	}
	return ENPROCESO;
}

void TimerSleepIRs(void){
	waiting = 2;
}

//Funcion de Handler de Timer1
void TimerFrenar(void){
	Tank_Brake();
	waiting = 1;
}

//Este es el codigo seguidor de lineas (solo utiliza ir del medio)
uint8_t ftl(void)	//se encarga del interior
{
	static uint8_t estado = CONTROL;

	switch(estado)
	{
		case CONTROL:

			if(Flag_Turn_ftl == 1)
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

			if(Flag_Turn_ftl == 0)
			{
				estado = CONTROL;
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
			if(Flag_Turn_ftl == 0)
			{
				estado = CONTROL;
			}

			break;

		case X10X:

			if(IR_IZQ_IN == 1 && IR_DER_IN == 1)
			{
				Tank_Forward(VELOCIDAD_FTL);
				estado = X11X;

			}

			if(Flag_Turn_ftl == 0)
			{
				estado = CONTROL;
			}

			break;

		case X01X:

			if(IR_IZQ_IN == 1 && IR_DER_IN == 1)
			{
				Tank_Forward(VELOCIDAD_FTL);
				estado = X11X;

			}
			if(Flag_Turn_ftl == 0)
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
/*


CODIGOS DESCARTADOS



#define		CRUCE			0
#define		NOCRUCE			1
#define		PRIMERCRUCE		2
#define		ESPERANDO		4


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

