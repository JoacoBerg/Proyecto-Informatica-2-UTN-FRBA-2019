/*******************************************************************************************************************************//**
 *
 * @file		Template.c
 * @brief		Breve descripción del objetivo del Módulo
 * @date		Fecha de creacion del archivo XX/XX/XXXX
 * @author		Nombre, Apellido
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "DR_tipos.h"
#include "DR_Entradas.h"
#include "DR_GPIO.h"
#include "DR_PINSEL.h"

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
__RW uint32_t BufferEntradas = 0;


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

void DebounceEntradas (void)
{

	static uint8_t ContadorEntradas[MAX_ENTRADAS] = {0};
	uint8_t in = 0, x;
	uint8_t i;

	if ( GetPin( E0 , BAJO) )
		in = 1;

	if ( GetPin( E1 , BAJO) )
		in |= 0x02;

	if ( GetPin( E2 , BAJO) )
		in |= 0x04;

	x = in ^ BufferEntradas;

	if ( !x )
	{
		for ( i=0 ; i < MAX_ENTRADAS ; i++ )
			ContadorEntradas[i] = 0;
	}
	else
	{
		for ( i=0 ; i<MAX_ENTRADAS ; i++ )
		{
			if ( x & (1<<i) )
			{
				ContadorEntradas[i]++;
				if ( ContadorEntradas[i] >= Rebotes )
						BufferEntradas = BufferEntradas ^ (1<<i);
			}
			else
				ContadorEntradas[i] = 0;
		}
	}
}


void InicializarEntradas ( void )
{
	//E0
	SetPinsel(E0, PINSEL_GPIO);
	SetPinMode(E0, PINMODE_PULLDOWN);
	SetPinDir(E0, PINDIR_INPUT);

	//E1
	SetPinsel(E1, PINSEL_GPIO);
	SetPinMode(E1, PINMODE_PULLDOWN);
	SetPinDir(E1, PINDIR_INPUT);

	//E2
	SetPinsel(E2, PINSEL_GPIO);
	SetPinMode(E2, PINMODE_PULLDOWN);
	SetPinDir(E2, PINDIR_INPUT);

}

