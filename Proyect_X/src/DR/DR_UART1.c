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
#include <DR_GPIO.h>
#include <DR_PINSEL.h>
#include "DR_UART1.h"
//#include "DR_EINT.h"
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
volatile uint8_t UART1_BufferRx[MAX_BUFF_RX1];
volatile uint8_t UART1_BufferTx[MAX_BUFF_TX1];
volatile uint8_t UART1_inRX,UART1_outRX,UART1_inTX,UART1_outTX;
volatile int16_t UART1_flagTx;

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

/**
	\fn  void UART1_IRQHandler (void)
	\brief Interrupcion de UART1
 	\author Ing. Marcelo Trujillo
 	\date 31 de ago. de 2016
 	\param void
	\return void
*/
void UART1_IRQHandler (void)
{

	uint8_t iir;
	int dato;

	do{
		iir = UART1IIR; //registro IIR se borra cuando lo leo

		switch( (iir >> 1) & 0x03)
		{
			case IIR_RDA:
				//BORRAR_RX; para otro micro habria que borrar flag de interrupcion por dato recibido
				dato = UART1RBR;
				UART1_PushRX ( (unsigned char) dato);
				break;

			case IIR_THRE:
				//BORRAR_TX; para otro micro habria que borrar flag de interrupcion por dato transmitido
				dato = UART1_PopTX();
				if( dato >= 0)
					UART1THR = (unsigned char) dato;
				else
					UART1_flagTx = 0;
				break;
		}
	}while(!(iir&0x01)); //me fijo si hay otra interrupcion pendiente de atencion


}

/**
	\fn  	void UART1_Inicializacion ( uint32_t baudios )
	\brief 	Inicializacion de UART1
 	\author Ing. Marcelo Trujillo
 	\date 	31 de ago. de 2016
	\return void
*/
void UART1_Inicializacion (void)
{
	PCONP |= 0x01<<4;	//prendo UART
		PCLKSEL0 |= (0x03<<8);		//	PLL/8		clock de UART

		//UART1LCR = 0x00000083;	//Tx de 8 bits, 1 bit de stop, sin paridad, sin break cond, habilito silicio para DLL y DLM (divisores) DLAB =1
		UART1LCR = 0x0000009b;		//Tx de 8 bits, 1 bit de stop, par, sin break cond, habilito silicio para DLL y DLM (divisores) DLAB =1
		//UART1LCR = 0x0000008b;		//Tx de 8 bits, 1 bit de stop, impar, sin break cond, habilito silicio para DLL y DLM (divisores) DLAB =1
		//UART1LCR = 0x00000087;	//Tx de 8 bits, 2 bit de stop, sin paridad, sin break cond, habilito silicio para DLL y DLM (divisores) DLAB =1

		//seteado a 115200 baud (PLL a 100Mhz)
		UART1DLM = 0;	//parte alta de divisor
		UART1DLL = 0x04;	//parte baja de divisor

		FDR_UART1 |= (0x05<<0);
		FDR_UART1 |= (0x08<<4);

		SetPinsel( TX1 , PINSEL_FUNC1);
		SetPinsel( RX1 , PINSEL_FUNC1);

		//UART1LCR = 0x03; // SIN PARIDAD habilito silicio para RBR y THR (buffer de recepcion y escritura) DLAB = 0
		//UART1LCR = 0x1b; // PARIDAD PAR habilito silicio para RBR y THR (buffer de recepcion y escritura) DLAB = 0
		UART1LCR = 0x0b; //   PARIDAD IMPARhabilito silicio para RBR y THR (buffer de recepcion y escritura) DLAB = 0
		//UART1LCR = 0x07; // SIN PARIDAD habilito silicio para RBR y THR (buffer de recepcion y escritura) DLAB = 0


		//Comentar para ej 1
		UART1IER = 0x03; //habilito interrupcion desde los registros de le UART0
		ISER0 |= (1<<6);  //habilito vector de interrupciones para UART0
		//fin del comentario
}

/**
	\fn  void UART1_PushRX( uint8_t dato )
	\brief pone un Byte en el buffer de recepcion
 	\author Ing. Marcelo Trujillo
 	\date 5 de oct. de 2017
 	\param [in] uint8_t dato Dato a guardar
	\return void
*/
void UART1_PushRX( uint8_t dato )
{
	UART1_BufferRx[ UART1_inRX ] = dato;
	UART1_inRX ++;
	UART1_inRX %= MAX_BUFF_RX1;
}

/**
	\fn int16_t UART1_PopTX( void )
	\brief saca un Byte en el buffer de transmicion
 	\author Ing. Marcelo Trujillo
 	\date 5 de oct. de 2017
 	\param void
	\return int16_t valor del dato o -1 por ERROR
*/
int16_t UART1_PopTX( void )
{
	int dato = -1;

	if( UART1_inTX != UART1_outTX )
	{
		dato = (unsigned int) UART1_BufferTx[UART1_outTX];
		UART1_outTX ++;
		UART1_outTX %= MAX_BUFF_TX1;
	}
	return dato;
}
