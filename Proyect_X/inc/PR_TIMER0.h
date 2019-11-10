/*
 * PR_TIMER0.h
 *
 *  Created on: Nov 6, 2019
 *      Author: GCRIS
 */

#ifndef PR_TIMER0_H_
#define PR_TIMER0_H_

#include "DR_PLL.h"
#include "DR_tipos.h"

#define ADC ((__RW adc_t *) 0x40034000UL)

#define CTCR ((__RW uint32_t*)  0x40004070UL)	//Count Control Register
#define PR ((__RW uint32_t*) 0x4000400CUL)	//Prescaler Register
#define TCR ((__RW uint32_t*) 0x40004004UL)	//Timer Control Register
#define TC ((__RW uint32_t*) 0x40004008UL)	//Timer Counter
#define PRESCALE (25000-1) //25000 PCLK clock cycles to increment TC by 1.
//CALCULO DE PRESCALE:
// PR = ( PCLK * T)-1		T: escala de tiempo
//
//	para este ejemplo en MS: PCLK=25Mhz = 25*10^6 hz
//							 T=10^-3 seg (milisegundos) -> (25 * 10^6 * 10^-3)-1 = 24999

void initTimer0(void);
void delayMS(unsigned int milliseconds); //Using Timer0


#endif /* PR_TIMER0_H_ */
