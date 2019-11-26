/*******************************************************************************************************************************//**
 *
 * @file		Maq_Caja.c
 * @brief		Descripcion del modulo
 * @date		3 nov. 2019
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "Maq_Caja.h"

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
static uint8_t estado = RESET;

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/
/**
	\fn  Nombre de la Funcion
	\brief Descripcion
 	\author Ing. Marcelo Trujillo
 	\date 3 nov. 2019
 	\param [in] parametros de entrada
 	\param [out] parametros de salida
	\return tipo y descripcion de retorno
*/

void init_led(uint8_t puerto, uint8_t pin)
{
	SetPinsel(puerto, pin, PINSEL_GPIO);
	SetPinMode(puerto, pin, PINMODE_PULLUP);
	SetPinDir(puerto, pin, PINDIR_OUTPUT);
}


void init_caja()
{
	init_led(PIN_RED);
	init_led(PIN_BLUE);
	init_led(PIN_GREEN);

	SERVO_CERRADO;
}

#define SEGUNDOS 2
//------------------EVENTOS--------------------------
#define E_WrongID		3
#define E_BlinkON 		4
#define E_BlinkOFF		5
#define E_Exit			6
#define E_BlinkGreenON	7
#define E_BlinkGreenOFF	8

//------------------TIEMPOS--------------------------
#define T_WrongID		2
#define T_BlinkRed		3 //en decimas
#define T_Exit			7
#define T_BlinkGreen	5 //en decimas
//------------------HANDLERS----------------------------------
void handler_BlinkOFF();
void handler_BlinkON();
void handler_BlinkGreenON();
void handler_BlinkGreenOFF();

//Bloquea acceso por tarjeta no valida
void handler_WrongID(){
	estado = BUSCAR_ID;
}

//Parpadeo hasta que termine tiempo de bloqueo
void handler_BlinkOFF(){
	RED_OFF;
	TimerStart(E_BlinkON, T_BlinkRed, handler_BlinkON, DEC );
}
void handler_BlinkON(){
	RED_ON;
	TimerStart(E_BlinkOFF, T_BlinkRed, handler_BlinkOFF, DEC );
}

//
void handler_Exit(){
	estado = SALIENDO;
}

//Parpadeo de estado con Caja LLENA
void handler_BlinkGreenOFF(){
	GREEN_OFF;
	TimerStart(E_BlinkGreenON, T_BlinkGreen, handler_BlinkGreenON, DEC );
}
void handler_BlinkGreenON(){
	GREEN_ON;
	TimerStart(E_BlinkGreenOFF, T_BlinkGreen, handler_BlinkGreenOFF, DEC );
}

uint8_t flag=0;
//-----------FIN DE HANDLERS-----------------------------------
// FUNCION Maq_Caja: se encarga de supervisar el estado de la caja
//return: exito si tarjeta ID, Boton e iman son correctos
uint8_t Maq_Caja( uint32_t num_base)
{
	uint8_t retorno =0 , card, flag_Wrong = 0;
	switch(estado)
	{
		case RESET:
			RED_OFF;
			GREEN_OFF;
			BLUE_OFF;
			SERVO_CERRADO;
			TimerStop(E_BlinkGreenOFF);
			TimerStop(E_BlinkGreenON);

			estado = BUSCAR_ID;
			break;

		case BUSCAR_ID:
			card = Card(num_base);
			if( card == 1)	// ID valido
			{
				SERVO_ABIERTO;
				RED_OFF;

				TimerStop(E_WrongID);	//por si acaso
				TimerStop(E_BlinkON); //termino blink
				TimerStop(E_BlinkOFF); //termino blink

				estado = BUSCAR_BOTON;
			}
			if( card == -1) //ID invalido
			{
				RED_ON;
				flag_Wrong++;
				TimerStart(E_WrongID, T_WrongID, handler_WrongID, SEG );
				TimerStart(E_BlinkON, T_BlinkRed, handler_BlinkON, DEC );
				estado = ESPERANDO;
			}
			if(!card)
				if(!flag_Wrong)
					RED_ON;

			break;

		case ESPERANDO: //para que no entre en default (ese es para RESET)
			break;


		case BUSCAR_BOTON:
			TimerStop(E_WrongID);
			TimerStop(E_BlinkON);
			TimerStop(E_BlinkOFF);

			if( BOTON )
			{
				BLUE_OFF;
				estado = BUSCAR_IMAN;
			}
			else
				BLUE_ON;

			break;

		case BUSCAR_IMAN:
			if(! IMAN)	// IMAN == 0 -> caja cerrada
			{
				SERVO_CERRADO;
				TimerStart(E_Exit, T_Exit, handler_Exit, SEG );
				GREEN_ON;
				estado = ESPERANDO;
			}
			else
			{
				BLUE_ON;
				estado = BUSCAR_BOTON;
			}
			break;

		case SALIENDO:
			TimerStop(E_Exit);
			retorno = 1;
			TimerStart(E_BlinkGreenON, T_BlinkGreen, handler_BlinkGreenON, DEC );
			estado = RESET;
			break;

		default:
			estado = RESET;
	}

	return retorno;
}
