/*
 * DR_systick.c
 *
 *  Created on: 6 sep. 2019
 *      Author: gif30
 */
#include <DR_Systick.h>

void SysTick_Init(void){
	Systick->STRELOAD = (Systick->STCALIB / 10) - 1; //Base de tiempo dada por 10ms/10: El -1 es porque cuenta uno de mas el STCURR
	Systick->STCURR = 0; //esto es para limpiar el timer

	Systick->ENABLE = 1; //activa el modulo
	Systick->TICKINT = 1; //activa la interrupcion
	Systick->CLKSOURCE = 1; //activa elige el clock del CPU en vez del clock externo por pin (STCLK)
}

void SysTick_Handler(void){

	//Hace la lectura de los IR cada 1 milisegundo
	static uint32_t timer = 1;

	if(timer)
		timer--;
	else
	{
		//LecturaIRs(IRx4);
		timer = 1;
	}


}
