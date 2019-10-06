/*
 * DR_SPI.c
 *
 *  Created on: Oct 5, 2019
 *      Author: GCRIS
 */
#include "DR_SPI.h"

void SPI_init(){

		GPIO_Pinsel( SCK_PIN , SPI_FUNCTION );
		GPIO_Mode( SCK_PIN, OUTPUT );

		GPIO_Pinsel( SSEL_PIN , SPI_FUNCTION );
		GPIO_Mode( SSEL_PIN, OUTPUT );

		GPIO_Pinsel( MISO_PIN , SPI_FUNCTION );
		GPIO_Mode( MISO_PIN, INPUT );

		GPIO_Pinsel( MOSI_PIN , SPI_FUNCTION );
		GPIO_Mode( MOSI_PIN, OUTPUT );


		PCONP |= (1<<8);	//alimentando periferico SPI

		PCLKSEL0 &= ~(3<<16);	//pongo 00 en SPI_CLCK
		PCLKSEL0 |= (SCK_CLCK<<16); //configuro Clock rate
		SPI->CLOCK = 8; //datasheet quiere minimo 8!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		SPI->CPHA=0; //empieza transferencia cuando BUFFER!=0

		SPI->MSTR = SPI_MODE;
}

uint8_t SPI_Write(uint8_t buffer)
{
	SPI->BUFFER = buffer;
	while( SPI->SPIF == 0); //SPIF=1 si finaliza con exito. SPIF=1 -> limpia bit

	return buffer; //se puede usar S0SPSR como debug (tiene flags)
}

uint8_t SPI_Read()
{
	while( SPI->SPIF ==0);

	return SPI->BUFFER;//cuando se lee se borra buffer
}
