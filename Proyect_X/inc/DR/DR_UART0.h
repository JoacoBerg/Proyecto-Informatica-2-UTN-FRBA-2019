/*******************************************************************************************************************************//**
 *
 * @file		DR_UART.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		12 de oct. de 2017
 * @author		Tanks
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef DRIVERLPC_DR_UART0_H_
#define DRIVERLPC_DR_UART0_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "DR_tipos.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define TOPE_BUFFER_RX		512
#define TOPE_BUFFER_TX		512

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/
//0x40010000UL : Registro de recepcion de la UART0:
#define		DIR_UART0		( ( __RW uint32_t  * ) 0x4000C000UL )

#define		UART0RBR		DIR_UART0[0]	// Registro de Recepción RBR
#define		UART0THR		DIR_UART0[0]	// Registro de Transmisión THR
#define		UART0DLL		DIR_UART0[0]	// Parte baja del divisor de la UART0:
#define		UART0IER			DIR_UART0[1]	// Registro de Habilitación de interrupciones de la UART0:
#define		UART0DLM		DIR_UART0[1]	// Parte Alta del divisor de la UART0:
#define		UART0IIR			DIR_UART0[2]	// Registro de Identificación de interrupciones de la UART0:
#define		UART0LCR		DIR_UART0[3]	// Line CONTROL Register de la UART0:
#define		UART0LSR		DIR_UART0[5]	// Line STATUS Register de la UART0:

//Macros UART0
#define		UART0DLAB_OFF	(U0LCR & 0xEF)
#define		UART0DLAB_ON	(U0LCR | 0x80)

#define 	TX0			0, 2	//Tx de la UART0
#define 	RX0			0, 3	//Rx de la UART0

//0x40010000UL : Registro de recepcion de la UART1:
#define		DIR_UART1		( ( __RW uint32_t  * ) 0x40010000UL )

#define		UART1RBR		DIR_UART1[0]
#define		UART1THR		DIR_UART1[0]
#define		UART1DLL		DIR_UART1[0]
#define		UART1IER			DIR_UART1[1]
#define		UART1DLM		DIR_UART1[1]
#define		UART1IIR			DIR_UART1[2]
#define		UART1LCR		DIR_UART1[3]
#define		UART1LSR		DIR_UART1[5]

#define 	TX1				PORT0 , 15	//Tx de la UART1
#define 	RX1				PORT0 , 16	//Rx de la UART1

#define		TXD			1
#define		RXD			1

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
extern volatile uint8_t UART0_BufferRx[];
extern volatile uint8_t UART0_BufferTx[];
extern volatile uint8_t IndiceRxIn , IndiceRxOut , IndiceTxIn, IndiceTxOut;
extern volatile int16_t TxStart;

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void UART0_Inicializacion (void );

void UART0_PushRX( uint8_t dato );
int16_t UART0_PopTX( void );

#endif /* DRIVERLPC_DR_UART0_H_ */
