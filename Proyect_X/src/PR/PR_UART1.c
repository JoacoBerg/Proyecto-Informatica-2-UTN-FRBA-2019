/*******************************************************************************************************************************//**
 *
 * @file		Template.c
 * @brief		Breve descripción del objetivo del Módulo
 * @date		Fecha de creacion del archivo XX/XX/XXXX
 * @author		Nombre, Apellido
 *
 */

#include "PR_UART1.h"
#include "DR_UART1.h"

/**
	\fn  int16_t UART1_PopRX( void )
	\brief saca un Byte en el buffer de recepcion
 	\author Ing. Marcelo Trujillo
 	\date 5 de oct. de 2017
 	\param void
	\return int16_t valor del dato o -1 por ERROR
*/
int16_t UART1_PopRX( void )
{
	int dato = -1;

	if( UART1_inRX != UART1_outRX )
	{
		dato = (unsigned int) UART1_BufferRx[UART1_outRX];
		UART1_outRX ++;
		UART1_outRX %= MAX_BUFF_RX1;
	}
	return dato;
}
/**
	\fn  void UART1_PushTX( uint8_t dato )
	\brief pone un Byte en el buffer de transmicion
 	\author Ing. Marcelo Trujillo
 	\date 5 de oct. de 2017
 	\param [in] uint8_t dato Dato a guardar
	\return void
*/
void UART1_PushTX( uint8_t dato )
{
	UART1_BufferTx[ UART1_inTX ] = dato;
	UART1_inTX ++;
	UART1_inTX %= MAX_BUFF_TX1;

	if(UART1_flagTx == 0)
	{
		UART1_flagTx = 1;
		UART1THR = UART1_PopTX();
	}
}
