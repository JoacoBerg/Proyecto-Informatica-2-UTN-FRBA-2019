
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
/**
 \fn  int main(void)
 \brief funcion principal
 \param void
 \return void
 */
void DebounceEntradas (void)
{

	static uint8_t ContadorEntradas[MAX_ENTRADAS] = {0};
	uint8_t in = 0, x;
	uint8_t i;

	if ( GetPin( IR1 , ALTO) )
		in = 1;

	if ( GetPin( IR2 , ALTO) )
		in |= 0x02;

	if ( GetPin( IR3 , ALTO) )
		in |= 0x04;

	if ( GetPin( IR4 , ALTO) )
		in |= 0x08;

	if ( GetPin( IR5 , ALTO) )
		in |= 0x10;

	if ( GetPin( PIN_IMAN , ALTO) )
		in |= 0x20;

	if ( GetPin( PIN_BOTON , ALTO) )
		in |= 0x40;


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


/**
	@fn  		void InicializarEntradas ( void )
	@brief 		Inicializacion de las entradas digitales
 	@author 	Ing. Marcelo Trujillo
 	@date 		8-11-16
 	@param 		void
	@return 	void
*/
void InicializarEntradas ( void )
{
	//IR1
	SetPinsel(IR1, PINSEL_GPIO);		//Funcion del pin
	SetPinMode(IR1, PINMODE_PULLDOWN);		//pull up? (or pull down) 0 = pull-up | 3 = pull-down?
	SetPinDir(IR1, PINDIR_INPUT);		//0: Entrada | 1: Salida

	//IR2
	SetPinsel(IR2, PINSEL_GPIO);		//Funcion del pin
	SetPinMode(IR2, PINMODE_PULLDOWN);		//pull up? (or pull down) 0 = pull-up | 3 = pull-down?
	SetPinDir(IR2, PINDIR_INPUT);		//0: Entrada | 1: Salida

	//IR3
	SetPinsel(IR3, PINSEL_GPIO);		//Funcion del pin
	SetPinMode(IR3, PINMODE_PULLDOWN);		//pull up? (or pull down) 0 = pull-up | 3 = pull-down?
	SetPinDir(IR3, PINDIR_INPUT);		//0: Entrada | 1: Salida

	//IR4
	SetPinsel(IR4, PINSEL_GPIO);		//Funcion del pin
	SetPinMode(IR4, PINMODE_PULLDOWN);		//pull up? (or pull down) 0 = pull-up | 3 = pull-down?
	SetPinDir(IR4, PINDIR_INPUT);		//0: Entrada | 1: Salida

	//BOTON
	SetPinsel( PIN_BOTON, PINSEL_GPIO);  //funcion GPIO configurada en pin
	SetPinMode( PIN_BOTON, PINMODE_PULLDOWN); //pull up
	SetPinDir( PIN_BOTON, PINDIR_INPUT); // input

	//IMAN
	SetPinsel( PIN_IMAN, PINSEL_GPIO);  //funcion GPIO configurada en pin
	SetPinMode( PIN_IMAN, PINMODE_PULLDOWN); //pull up
	SetPinDir( PIN_IMAN, PINDIR_INPUT); // input

}
