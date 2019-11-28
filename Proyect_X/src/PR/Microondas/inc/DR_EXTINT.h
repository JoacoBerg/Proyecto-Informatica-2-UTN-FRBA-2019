/*
 * DR_EXTINT.h
 *
 *  Created on: Nov 27, 2019
 *      Author: GCRIS
 */

#ifndef DR_EXTINT_H_
#define DR_EXTINT_H_
#include "DR_PINSEL.h"


#define		EXTINT		( ( uint32_t  * )	0x400FC140UL )
#define		EXTMODE		( ( uint32_t  * )	0x400FC148UL )
#define		EXTPOLAR	( ( uint32_t  * )	0x400FC14CUL )

// FUNCIONAMIENTO:	el microcontrolador LPC1769 tiene 4 pines que pueden ser
//					configurados para interrupciones externas, captando la señal de entrada.
//					1) PINSEL: configurar pines como EINT0-3
//					2) ISER: habilitar funcion EINTx_IRQHandler() del vector de interrupciones NVIC
//					3) EXTINT: poner bitEINT en 1 para bajar flag (ISER ve ese flag), se activa cuando hay interrupcion
//					4) EXTMODE: modo '0': NIVEL , '1': FLANCO
//					5) EXTPOLAR: modo '0': Activo BAJO , '1': Activo ALTO
//
//					6) EINTx_IRQHandler(): escribir funcion

//----------- PINSEL -----------//
#define PINSEL_EXTINT	1

//----------- VECTOR INTERRUPCIONES (NVIC) -----------//
#define	ISER_EINT0		18
#define ISER_EINT3		21

//----------- PINES (PLACA INFOTRONIC -> SW) -----------//
#define SW1				2,10 //EINT0
#define SW10			2,13 //EINT3

void init_extINT();

#endif /* DR_EXTINT_H_ */
