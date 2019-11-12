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
//#include <DR_IR.h>
#include <Maq_FollowTheLine.h>
#include "Tanks.h"
#include "DR_tipos.h"
#include "PR_Entradas.h"
#include "PR_Timers.h"
#include <DR_PINSEL.h>
#include "PR_UART0.h"

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
//#define 	RESET		0
#define 	PRIMERCRUCE		1
#define 	NOCRUCE			2
#define 	WAITING			3
#define 	WAITING_FRENO	4
#define 	RESTARTING		5


//Velocidad del Auto
#define		VELOCIDAD_FTL 80

//Timers
#define		TIMER_FRENO 			1
#define		TIMER_SLEEP_IRs			4
#define 	TIMER_SLEEP_OBSTACULO	5
#define 	TIMER_RESTART			6


//Flags de las maquinas de estado
uint8_t Flag_Turn_ftl = OFF;

//Flags de los TIMERS
uint8_t waiting_IRs = OFF;
uint8_t waiting_OBSTACULO = ON;
uint8_t waiting_freno = OFF;
uint8_t waiting_Restart = OFF;

//Handlers de timer
void TimerFrenar(void);
void TimerSleepIRs(void);
void TimerSleepOBSTACULO(void);
void TimerRestart(void);


/*
 * Maq_FollowTheLine_v2(), es una maquina de estados que se encarga de detectar cuando el auto pasa por un cruce
 * Esta maquina es la que prende y apaga a flt(), para que el auto pueda avanzar en linea recta.
 * Por otro lado, tiene integrada la deteccion de obstaculos en el camino. En caso de detectar un objeto en el camino
 * se detendra automaticamente, cuando el objeto es retirdo arrancara despues de un tiempo determinado
 * No recibe ningun parametro
 * Devuelve: - EXITO: 		si detecto un cruce
 * 			 - ENPROCESO:	si no detecto un cruce
 */
uint8_t Maq_FollowTheLine_v2(void)
{
	static uint8_t estado2 = RESET;
	static uint8_t estado_obstaculo = RESET;
	static uint8_t estado_aux = RESET;
	static uint8_t Flag_Turn_ftl_aux = OFF; //Flag para "prender" o "apagar" ftl()
	static uint8_t waiting_IRs_aux = OFF;

	if(estado_obstaculo == RESET){

		if (IR_OBSTACULO == OFF && waiting_OBSTACULO == ON){ //IR_OBSTACULO ESTA AL REVES (OFF = hay obstaculo)
			//guardo variables en estados auxiliares
			estado_aux = estado2;
			Flag_Turn_ftl_aux = Flag_Turn_ftl;
			waiting_IRs_aux = waiting_IRs;
			//freno todo
			Flag_Turn_ftl = OFF;
			TimerStop(TIMER_SLEEP_IRs);
			estado_obstaculo = WAITING_FRENO;
		}

		else{

			switch(estado2)
			{
				case RESET:

					Flag_Turn_ftl = ON;
					waiting_IRs = OFF;// para que no entre a ningun if de WAITING
					TimerStart(TIMER_SLEEP_IRs, 4, TimerSleepIRs, DEC);
					estado2 = WAITING;
					break;

				case WAITING:

					if(waiting_IRs == ON)
						estado2 = NOCRUCE;
					break;

				case NOCRUCE:

					if(IR_IZQ_OUT == ON && IR_DER_OUT == ON){
						estado2 = RESET;
						return EXITO;
					}
					break;

				default:

					estado2 = RESET;
					break;
			}
		}
	}
	else if (estado_obstaculo == WAITING_FRENO){
		if(Maq_Freno()){
			UART0_SendString("Obstaculo detectado");
			estado_obstaculo = WAITING;
		}
	}
	else if (estado_obstaculo == WAITING){

		if(IR_OBSTACULO == ON){
			UART0_SendString("Retomando Ruta");
			waiting_Restart = OFF;
			TimerStart(TIMER_RESTART, 1, TimerRestart, SEG);
			estado_obstaculo = RESTARTING;
		}
		else{
			/*nada*/
		}
	}
	else if (estado_obstaculo == RESTARTING){
		 if(waiting_Restart == ON){

			estado2 = estado_aux;
			Flag_Turn_ftl = Flag_Turn_ftl_aux;
			waiting_IRs = waiting_IRs_aux;
			if(estado2 == WAITING){
				TimerStart(TIMER_SLEEP_IRs, 4, TimerSleepIRs, DEC);
			}

			TimerStart(TIMER_SLEEP_OBSTACULO, 2, TimerSleepOBSTACULO, DEC);
			estado_obstaculo = RESET;
		 }
	}
	return ENPROCESO;
}


//Funciones de handlers de timers para Maq_FollowTheLine_v2()
void TimerSleepIRs(void){
	waiting_IRs = ON;
}

void TimerRestart(void){
	waiting_Restart = ON;
}

void TimerSleepOBSTACULO(void){
	waiting_OBSTACULO = ON;
}

void TimerFrenar(void){
	Tank_Brake();
	waiting_freno = ON;
}


/*
 * Maq_Freno(), Es una maquina de estados para lograr que el auto frene en el lugar.
 * Haciendo que vaya para atras una decima de segundo
 * No recibe ningun parametro
 * Devuelve: - EXITO: 		si ya termino de frenar
 * 			 - ENPROCESO:	si no termino de frenar
 */
uint8_t Maq_Freno(void){
	static uint8_t estado = RESET;
	switch(estado)
	{

		case RESET:

			Flag_Turn_ftl = OFF;
			Tank_Brake();
			Tank_Backward(VELOCIDAD_FTL);
			TimerStart(TIMER_FRENO, 1, TimerFrenar, DEC); //hago que vaya 1 decima de segundo para atras para que frene en el lugar
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

/*
 * ftl(), Es la maquina de estados que hace posible que el auto siga un linea negra (solamente con los Sensores IR del centro)
 * Si detecta que se desvia hacia la derecha gira levemente a la izquiera y veceversa.
 * No recibe ningun parametro
 * No devuelve ningun parametro
 */
uint8_t ftl(void)
{
	static uint8_t estado = CONTROL;

	switch(estado)
	{
		case CONTROL:

			if(Flag_Turn_ftl == ON)
				estado = RESET;
			else
				estado = CONTROL;
			break;

		case RESET:

			Tank_Forward(VELOCIDAD_FTL);
			estado = X11X;

			if(Flag_Turn_ftl == OFF)
				estado = CONTROL;
			break;

		case X11X:

			if(IR_IZQ_IN == OFF && IR_DER_IN == ON){
				Tank_Right(VELOCIDAD_FTL);
				estado = X01X;
			}

			if(IR_IZQ_IN == ON && IR_DER_IN == OFF){
				Tank_Left(VELOCIDAD_FTL);
				estado = X10X;
			}

			if(Flag_Turn_ftl == OFF)
				estado = CONTROL;
			break;

		case X10X:

			if(IR_IZQ_IN == ON && IR_DER_IN == ON){
				Tank_Forward(VELOCIDAD_FTL);
				estado = X11X;
			}

			if(Flag_Turn_ftl == OFF)
				estado = CONTROL;
			break;

		case X01X:

			if(IR_IZQ_IN == ON && IR_DER_IN == ON){
				Tank_Forward(VELOCIDAD_FTL);
				estado = X11X;
			}

			if(Flag_Turn_ftl == OFF)
				estado = CONTROL;
			break;

		case ALARMA:

			return FALLO;
			break;

		default:
			estado = CONTROL;
			break;
		}

	return ENPROCESO;
}

//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
//------------------------------FIN MAQUINA DE ESTADOS DE FOLLOW THE LINE---------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------


