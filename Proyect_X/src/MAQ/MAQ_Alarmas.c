 /*******************************************************************************************************************************//**
 *
 * @file		MAQ_Alarmas.c
 * @brief		Descripcion del modulo
 * @date		8 dic. 2019
 * @author		Tanks
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "MAQ_Alarmas.h"
#include "PR_Entradas.h"
#include "PR_Timers.h"
#include "PR_UART0.h"

#include "Maq_GRAL.h"


/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
#define RESET_AL 		0
#define FUNCAx4			1
#define ESPERANDOx4		2
#define ALARMA_MAQ		3
#define CHECKOBS		4
#define ESPERANDO_OBS   5
#define SOBRERUEDAS		6

//---------Timers---------
#define ev_esperandox4  8
#define ev_esperandoObs 9
#define ev_obsRoto 		10

//---------Timers---------
#define t_esperandox4  5 //seg
#define t_esperandoObs 2 //dec
#define t_obsRoto      3 //seg

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
uint8_t estAl = RESET_AL;
/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
void f_esperandox4(void);
void f_esperandoObs(void);
void f_obsRoto(void);
 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/

uint8_t Maq_Alarma(void)
{

static	uint8_t flag_esperandox4 = 0;
static 	uint8_t flag_esperandoObs = 0;


	switch (estAl) {
		case RESET_AL:

			if(IR_IZQ_IN == ON && IR_DER_IN == ON && IR_IZQ_OUT == ON && IR_DER_OUT == ON)
			{
				estAl = FUNCAx4;
			}
			else
			{
				estAl = ESPERANDOx4;
				UART0_SendString("Auto mal colocado");
			}

			break;

		case FUNCAx4:

			UART0_SendString("Auto bien colocado");
			estAl = CHECKOBS;
			break;

		case CHECKOBS:

			if(IR_OBSTACULO == OFF) //OFF --> ON
			{
				TimerStart(ev_esperandoObs, t_esperandoObs, f_esperandoObs, DEC);
			}
			break;

		case ESPERANDO_OBS:

			if(flag_esperandoObs == 0)
			{
				UART0_SendString("Quite el obstaculo");
				TimerStart(ev_obsRoto, t_obsRoto, f_obsRoto, SEG);
				flag_esperandoObs = 1;
			}

			if(IR_OBSTACULO == ON) //ON --> OFF
			{
				UART0_SendString("SensorObs: ok");
				estAl = SOBRERUEDAS;
				TimerStop(ev_esperandoObs);
				TimerStop(ev_esperandox4);
				TimerStop(ev_obsRoto);
				//return EXITO;
			}
			break;

		case ESPERANDOx4:

			if(flag_esperandox4 == 0)
			{

				TimerStart(ev_esperandox4, t_esperandox4, f_esperandox4, SEG);
				flag_esperandox4 = 1;
			}

			if(IR_IZQ_IN == ON && IR_DER_IN == ON && IR_IZQ_OUT == ON && IR_DER_OUT == ON)
			{
				estAl = FUNCAx4;
			}

			break;

		case ALARMA_MAQ:
			if(flag_esperandox4 == 1)
			{
				if(IR_IZQ_IN == ON && IR_DER_IN == ON && IR_IZQ_OUT == ON && IR_DER_OUT == ON)
				{
					estAl = FUNCAx4;
				}
			}
			/*hacer mierda todo*/
			//LED_ON
			break;

		case SOBRERUEDAS:

			Maq_General();
			estAl = SOBRERUEDAS;
			break;

		default:
			estAl = RESET_AL;
			break;
	}
	return ENPROCESO;


}

//------Funciones timers----------
void f_esperandox4(void)
{
	if(IR_IZQ_IN == OFF)
		UART0_SendString("ALARMA:'IR_IZQ_IN' Roto");

	if(IR_DER_IN == OFF)
		UART0_SendString("ALARMA:'IR_DER_IN' Roto");

	if(IR_IZQ_OUT == OFF)
		UART0_SendString("ALARMA:'IR_IZQ_OUT' Roto");

	if(IR_DER_OUT == OFF)
		UART0_SendString("ALARMA:'IR_DER_OUT' Roto");

	estAl = ALARMA_MAQ;
	//LED_ON
}

void f_esperandoObs(void)
{
	estAl = ESPERANDO_OBS;
}

void f_obsRoto(void)
{
	estAl = ALARMA_MAQ;
	UART0_SendString("SensorObs: Defectuoso");
}

