/*******************************************************************************************************************************//**
 *
 * @file		DR_UART.c
 * @brief		Descripcion del modulo
 * @date		12 de oct. de 2017
 * @author		Tanks
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "DR_UART0.h"
#include "DR_gpio.h"
#include "DR_pinsel.h"
#include "DR_PLL.h"

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
volatile uint8_t UART0_BufferRx[TOPE_BUFFER_RX];
volatile uint8_t UART0_BufferTx[TOPE_BUFFER_TX];
volatile uint8_t IndiceRxIn , IndiceRxOut , IndiceTxIn, IndiceTxOut;
volatile int16_t TxStart;

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/

#define IIR_RDA 2
#define IIR_THRE 1

void UART0_IRQHandler (void)
{
	uint8_t iir;
	int dato;

	do{
		iir = UART0IIR; //registro IIR se borra cuando lo leo

		switch( (iir >> 1) & 0x03)
		{
			case IIR_RDA:
				//BORRAR_RX; para otro micro habria que borrar flag de interrupcion por dato recibido
				dato = UART0RBR;
				UART0_PushRX ( (unsigned char) dato);
				break;

			case IIR_THRE:
				//BORRAR_TX; para otro micro habria que borrar flag de interrupcion por dato transmitido
				dato = UART0_PopTX();
				if( dato >= 0)
					UART0THR = (unsigned char) dato;
				else
					TxStart = 0;
				break;
		}
	}while(!(iir&0x01)); //me fijo si hay otra interrupcion pendiente de atencion

}

void UART0_Inicializacion ( void )
{
	PCONP |= 0x01<<3;	//prendo UART
	PCLKSEL0 &= ~(0x03<<6);		//clock de UART

	UART0LCR = 0x00000083;	//Tx de 8 bits, 1 bit de stop, sin paridad, sin break cond, habilito silicio para DLL y DLM (divisores) DLAB =1
	//seteado a 9600 baud (PLL a 100Mhz)
	UART0DLM = 0;	//parte alta de divisor
	UART0DLL = 0xA3;	//parte baja de divisor

	SetPinsel( TX0 , PINSEL_FUNC1);
	SetPinsel( RX0 , PINSEL_FUNC1);
	UART0LCR = 0x03; //habilito silicio para RBR y THR (buffer de recepcion y escritura) DLAB = 0

	UART0IER = 0x03; //habilito interrupcion desde los registros de le UART0
	ISER0 |= (1<<5);  //habilito vector de interrupciones para UART0
}

void UART0_PushRX( uint8_t dato )
{
	UART0_BufferRx[ IndiceRxIn ] = dato;
		IndiceRxIn ++;
		IndiceRxIn %= TOPE_BUFFER_RX;
}

int16_t UART0_PopTX( void )
{
	int dato = -1;

	if( IndiceTxIn != IndiceTxOut )
	{
		dato = (unsigned int) UART0_BufferTx[IndiceTxOut];
		IndiceTxOut ++;
		IndiceTxOut %= TOPE_BUFFER_TX;
	}
	return dato;
}
