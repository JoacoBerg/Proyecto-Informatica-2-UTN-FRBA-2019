/*
 * DR_systick.c
 *
 *  Created on: 6 sep. 2019
 *      Author: gif30
 */
#include <DR_Systick.h>
#define TIEMPO_ADC 1000
#include "DR_ADC.h"

uint32_t resultado = 0;

void SysTick_Init(void){
	Systick->STRELOAD = (Systick->STCALIB / 10) - 1; //Base de tiempo dada por 10ms/10: El -1 es porque cuenta uno de mas el STCURR
	Systick->STCURR = 0; //esto es para limpiar el timer

	Systick->ENABLE = 1; //activa el modulo
	Systick->TICKINT = 1; //activa la interrupcion
	Systick->CLKSOURCE = 1; //activa elige el clock del CPU en vez del clock externo por pin (STCLK)
}

void SysTick_Handler(void){
static uint32_t timer= TIEMPO_ADC;
if(timer)
	timer--;
else{
	resultado = RESULT_ADC;
	//ADC->START = 1;
	timer = TIEMPO_ADC;
}
}
