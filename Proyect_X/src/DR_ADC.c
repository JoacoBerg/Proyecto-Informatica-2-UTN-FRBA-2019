/*
 * DR_ADC.c
 *
 *  Created on: 13 sep. 2019
 *      Author: gif30
 */

#include "DR_ADC.h"

void ADC_init(void){
	PCONP |= (1<<12);	//prender el modulo de ADC

	PCLKSEL0 &= ~(3<<24);	//pongo la frequencia mas baja 100/4MHz = 25MHz | PCLK_peripheral = CCLK/4
	//PCLKSEL0 |= (1<<24);	//USAR PARA CAMBIAR A OTRA DIVISION

	ADC->CLKDIV = 1; // 12/13 Hz = CLKDIV = (fclkADC/65 - fADC)/fADC, fADC=200KHz , fclkADC=25MHz



	ISER[0] |= (1<<22);			//habilito interrupcion

	GPIO_Pinsel(GPIO_ADC5, 3);	//ELIJO EL ADC 5 NOMAS PORQ PINTO
	ADC->SEL_ADC5 = 1; 		//SOLO EL 5. una seleccion del ADC5 dentro del modulo
	ADC->PDN = 1;			//power on del modulo (sirve para ponerlo en bajo consumo cuando no se usa)
	ADC->ADINTEN5 = 1;		//habilita interrupcion del ADC5
}
