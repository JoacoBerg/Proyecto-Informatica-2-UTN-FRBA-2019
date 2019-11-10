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
#define E_WrongID	3
#define E_BlinkRed 	4
#define E_Exit		5
//------------------TIEMPOS--------------------------
#define T_WrongID	7
#define T_BlinkRed	3
#define T_Exit		7
uint32_t blink=0;

//------------------Handlers--------------------------
//Bloquea acceso por tarjeta no valida
void handler_WrongID(){
	estado = BUSCAR_ID;
}
//Parpadeo hasta que termine tiempo de bloqueo
void handler_BlinkRed(){
	if(blink%2)
	{
		RED_OFF;
		blink++;
	}
	else
	{
		RED_ON;
		blink++;
	}
	TimerStart(E_BlinkRed, T_BlinkRed, handler_BlinkRed, SEG );
}

void handler_Exit()
{
	estado = SALIENDO;
}
uint8_t flag=0;

// FUNCION Maq_Caja: se encarga de supervisar el estado de la caja
//return: exito si tarjeta ID, Boton e iman son correctos
uint8_t Maq_Caja()
{
	uint8_t retorno =0 , card, flag_Wrong = 0;
	switch(estado)
	{
		case RESET:
			RED_OFF;
			GREEN_OFF;
			BLUE_OFF;
			SERVO_CERRADO;

			estado = BUSCAR_ID;
			break;

		case BUSCAR_ID:
			card = Card();
			if( card == 1)	// ID valido
			{
				SERVO_ABIERTO;
				RED_OFF;

				TimerStop(E_WrongID);	//por si acaso
				TimerStop(E_BlinkRed); //termino blink

				estado = BUSCAR_BOTON;
			}
			if( card == -1) //ID invalido
			{
				RED_ON;
				flag_Wrong++;
				TimerStart(E_WrongID, T_WrongID, handler_WrongID, SEG );
				TimerStart(E_BlinkRed, T_BlinkRed, handler_BlinkRed, SEG );
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
			TimerStop(E_BlinkRed);

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
			estado = RESET;
			break;

		default:
			estado = RESET;
	}

	return retorno;
}
