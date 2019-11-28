/*
 * DR_EXTINT.c
 *
 *  Created on: Nov 27, 2019
 *      Author: GCRIS
 */
#include "Microondas.h"
#include "PR_Maq_Recibo.h"
#include "DR_Salidas.h"

void EINT0_IRQHandler()
{
	EXTINT[0] |= (1<<1); 		//bajar flag de interrupcion
	TimerStop(E_DESCONTAR1);
	TimerStop(E_DESCONTAR2);
	TimerStop(E_COOK);
	RELAY_OFF;
	tempo=0;
	flag_Cooking=0;	//no cocinando hasta que flag = 1
 	flagDesc = 0; 	//descuento de segundos

	estado = RESET;
}

void init_extINT()
{
	/* INIT EXT INT	*/
	ISER[0] |= (1<<ISER_EINT0);			//habilito interrupcion
	SetPinsel( SW1 , PINSEL_EXTINT);
	EXTINT[0] |= (1<<1); 		//bajar flag de interrupcion
	EXTMODE[0]|= ~(1<<1);		//modo '0': NIVEL , '1': FLANCO
	EXTPOLAR[0] |= (1<<1);		//modo '0': Activo BAJO , '1': Activo ALTO
}
