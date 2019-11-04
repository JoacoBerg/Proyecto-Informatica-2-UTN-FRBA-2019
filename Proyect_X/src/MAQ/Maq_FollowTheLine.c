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
uint8_t Flag_Control = 0;
uint8_t flag_TB = 0; //este flag sirve para que frene con el timer (este timer tiene injerencia en ftl())
uint8_t waiting = 0;
uint8_t estado2 = RESET2;




//Maquina que detecta cruces y llama a ftl()
uint8_t Maq_FollowTheLine_v2(void)
{
	//static uint8_t cruce = 0; //sirve para saber si arrancaste en un cruce
							  // 0 = arranco en cruce
							  // 1 = ya salio del primer cruce | no arranco en cruce
switch(estado2)
	{

//probando cosas maravillosas
/*		case RESET2:

			if((IR_IZQ_OUT == 1 && IR_DER_OUT == 1) | (IR_IZQ_OUT == 1) | (IR_DER_OUT == 1))// si esta uno, el otro o los dos prendidos, arranca en primer cruce
			{
				Flag_Control = ON;
				cruce = 0;
				estado2 = PRIMERCRUCE;
			}

			else if(IR_IZQ_OUT == 0 && IR_DER_OUT == 0)
			{
				Flag_Control = ON;
				cruce = 1;
				estado2 = NOCRUCE;
			}
			break;

		case PRIMERCRUCE:
			if(cruce == 0)
			{
				Flag_Control = ON;
				estado2 = PRIMERCRUCE;
			}

			else if(IR_IZQ_OUT == 0 && IR_DER_OUT == 0)
			{
				Flag_Control = ON;
				cruce = 1;
				estado2 = NOCRUCE;
			}
			break;
*/
		case RESET2:
			Flag_Control = ON;
			TimerStart(4, 7, timer4, DEC);
			estado2 = WAITING;
			waiting = 0;// para que no entre a ningun if de WAITING
			break;

		case NOCRUCE:
			/*if(cruce == 1)
			{
				Flag_Control = ON;
				estado2 = NOCRUCE;
			}
			*/

			if(IR_IZQ_OUT == 1 && IR_DER_OUT == 1)
			{
				Tank_Brake();
				Tank_Backward(VELOCIDAD_FTL);
				TimerStart(1, 1, TimerFrenar, DEC); //hago que vaya 1 decima de segundo para atras para que frene en el lugar
				flag_TB = 1; //este flag sirve para que frene con el timer (este timer tiene injerencia en ftl())
							 //si esta en 1 frena con el Timer
				//cruce = 0;
				estado2 = WAITING;
				waiting = 0;
				Flag_Control = OFF;

			}

			Flag_Control = ON;

			break;

			case WAITING:
				if(waiting == 1)
				{
					estado2 = RESET2;
					return EXITO;
				}
				else if(waiting == 2)
				{
					Flag_Control = ON;
					estado2 = NOCRUCE;
				}
				break;

		default:
			estado2 = RESET2;
			break;
	}
	return ENPROCESO;
}

void timer4(void)
{
	waiting = 2;
}

//Funcion de Handler de Timer1
void TimerFrenar(void)
{
	Tank_Brake();
	waiting = 1;
	flag_TB = 0; //este flag sirve para que frene con el timer (este timer tiene injerencia en ftl())
}

//Este es el codigo seguidor de lineas (solo utiliza ir del medio)
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
				if(flag_TB ==0) Tank_Brake(); //habria que probrar si la maquina deja de andar bien por no poner este Tank_Brake()
											  //El if() esta para que no se active esta linea si hay un timer para frenar al auto
											  //Maq_FollowTheLine_v2()
			}
			break;

		case RESET:

			Tank_Forward(VELOCIDAD_FTL);
				estado = X11X;

			if(Flag_Control == 0)
			{
				estado = CONTROL;
				if(flag_TB ==0) Tank_Brake();
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
				if(flag_TB ==0) Tank_Brake();
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
				if(flag_TB ==0) Tank_Brake();
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
				if(flag_TB ==0) Tank_Brake();
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

