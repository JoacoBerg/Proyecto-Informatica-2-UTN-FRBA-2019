/*
 * DR_ADC.c
 *
 *  Created on: 13 sep. 2019
 *      Author: gif30
 */

#include "DR_ADC.h"

void ADC_init(void){
	PCONP |= (1<<12);

	PCLKSEL0 &= ~(3<<24);
	//PCLKSEL0 |= (1<<24);

	ADC->CLKDIV = 1; // 12/13 Hz = CLKDIV = (fclkADC/65 - fADC)/fADC, fADC=200KHz , fclkADC=25MHz

	GPIO_Pinsel(GPIO_ADC5, 3);

	ISER[0] |= (1<<22);


	ADC->SEL_ADC5 = 1; //SOLO EL 5
	ADC->PDN = 1;
	ADC->ADINTEN5 = 1;
}
