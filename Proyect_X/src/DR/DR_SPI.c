/*
 * DR_SPI.c
 *
 *  Created on: Oct 5, 2019
 *      Author: GCRIS
 */
//CONTIENE PRIMITIVAS DE WRITE Y READ
#include "DR_SPI.h"
#include "DR_PINSEL.h"

void SPI_init(){
		uint8_t limpieza;

		SetPinsel( SCK_PIN , SPI_FUNCTION );
		SetPinsel( SSEL_PIN , PINSEL_GPIO );
		SetPinMode( SSEL_PIN, PINMODE_PULLUP );
		SetPinDir(SSEL_PIN, PINDIR_OUTPUT);
		SetPin( SSEL_PIN, HIGH ); //se pone en LOW para iniciar transferencia

		SetPinsel( MISO_PIN , SPI_FUNCTION );

		SetPinsel( MOSI_PIN , SPI_FUNCTION );


		PCONP |= (1<<8);	//alimentando periferico SPI

		PCLKSEL0 &= ~(3<<16);	//pongo 00 en SPI_CLCK
		PCLKSEL0 |= (SCK_CLCK<<16); //configuro Clock rate
		SPI->S0SPCCR = 8; //8: clock a 12,5MHz

		SPI->CPHA=0; //empieza transferencia cuando BUFFER!=0

		SPI->MSTR = SPI_MODE; //define modo
		SPI->BitEnable = 1;
		SPI->BITS = 0; //seteando 16 bits

		limpieza = SPI->S0SPSR;
		limpieza = SPI->S0SPDR;
		limpieza = limpieza;
}
