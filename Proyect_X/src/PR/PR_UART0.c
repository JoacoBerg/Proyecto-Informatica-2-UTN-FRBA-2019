/*
 * PR_UART0.c
 *
 *  Created on: Oct 31, 2019
 *      Author: augusto
 */

#include "DR_UART0.h"
#include "PR_UART0.h"

/**
	\fn  int16_t PopRX( void )
	\brief saca un Byte en el buffer de recepcion
 	\author Ing. Marcelo Trujillo
 	\date 5 de oct. de 2017
 	\param void
	\return int16_t valor del dato o -1 por ERROR
*/
int16_t UART0_PopRX( void )
{
	int dato = -1;

	if( IndiceRxIn != IndiceRxOut )
	{
		dato = (unsigned int) UART0_BufferRx[IndiceRxOut];
		IndiceRxOut ++;
		IndiceRxOut %= TOPE_BUFFER_RX;
	}
	return dato;
}

/**
	\fn  void PushTX( uint8_t dato )
	\brief pone un Byte en el buffer de transmicion
 	\author Ing. Marcelo Trujillo
 	\date 5 de oct. de 2017
 	\param [in] uint8_t dato Dato a guardar
	\return void
*/
void UART0_PushTX( uint8_t dato )
{
	UART0_BufferTx[ IndiceTxIn ] = dato;
		IndiceTxIn ++;
		IndiceTxIn %= TOPE_BUFFER_TX;

		if(TxStart == 0)
		{
			TxStart = 1;
			UART0THR = 1;
		}
}
