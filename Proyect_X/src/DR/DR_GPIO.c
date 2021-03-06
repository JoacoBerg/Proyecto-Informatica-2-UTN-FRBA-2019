/*******************************************************************************************************************************//**
 *
 * @file		Infotronic.c
 * @brief		Drivers de GPIO LPC1769
 * @date		23-03-16
 * @author		Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <DR_GPIO.h>
#include <DR_tipos.h>

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

void SetPinDir(uint32_t Puerto, uint32_t Pin,uint32_t Dir){	//0: Entrada; 1: Salida

	if(Dir)
		GPIOs[Puerto].FIODIR|=(1<<Pin);
	else
		GPIOs[Puerto].FIODIR&=~(1<<Pin);
}


void SetPinMode(uint32_t Puerto, uint32_t Pin,uint32_t Modo){	//pull up or pull down

	PINMODE[(Puerto*2) + (Pin/16)]&=~(3<<((Pin%16) * 2));
	PINMODE[(Puerto*2) + (Pin/16)]|=(Modo<<((Pin%16) * 2));
}


void SetPinMode_OD(uint32_t Puerto, uint32_t Pin,uint32_t Modo){	//0 normal | 1 open collector (open drain)

	PINMODE_OD[Puerto] &= ~(1<<Pin);
	PINMODE_OD[Puerto] |= (Modo<<Pin);
}



void SetPin(uint32_t Puerto, uint32_t Pin, uint32_t Estado){	//escritura del GPIO

	if(1==Estado)	//Buena practica de programacion: en lugar de if(Estado==1)
		GPIOs[Puerto].FIOSET = (1<<Pin);
	else
		GPIOs[Puerto].FIOCLR = (1<<Pin);
}


/*
uint32_t GetPin(uint32_t Puerto, uint32_t Pin){	//lectura del GPIO

		if(GPIOs[Puerto].FIOPIN & (1<<Pin))
			return 1;
		else
			return 0;

}*/

uint32_t GetPin( uint8_t puerto , uint8_t bit , uint8_t actividad )
{
	__RW uint32_t *p = ( __RW uint32_t * )  0x2009C014 ;
	uint8_t r;

	r = ( *( p + puerto * 8 ) >> bit ) & 1;
	if ( actividad )
		return r;
	return !r;
}

