/*
 * DR_ADC.c
 *
 *  Created on: 13 sep. 2019
 *      Author: gif30
 */

#include "DR_ADC.h"
uint32_t RESULT_ADC = 0 ;
#define CANT_MUESTRAS 10
uint32_t muestras[CANT_MUESTRAS];

void ADC_init(void){
	PCONP |= (1<<12);	//prender el modulo de ADC

	PCLKSEL0 &= ~(3<<24);	//pongo la frequencia mas baja 100/4MHz = 25MHz | PCLK_peripheral = CCLK/4
	//PCLKSEL0 |= (1<<24);	//USAR PARA CAMBIAR A OTRA DIVISION

	ADC->CLKDIV = 1; // 12/13 Hz (que es aproximadamente 1Hz) = CLKDIV = (fclkADC/65 - fADC)/fADC, fADC=200KHz , fclkADC=25MHz



	ISER[0] |= (1<<22);			//habilito interrupcion

	GPIO_Pinsel(GPIO_ADC5, 3);	//ELIJO EL ADC 5 NOMAS PORQ PINTO
	ADC->SEL_ADC5 = 1; 		//SOLO EL 5. una seleccion del ADC5 dentro del modulo
	ADC->PDN = 1;			//power on del modulo (sirve para ponerlo en bajo consumo cuando no se usa)
	ADC->ADINTEN5 = 1;		//habilita interrupcion del ADC5

	ADC->START = 1;		//lo hacemos arrancar

	for (int i=0;i<CANT_MUESTRAS;i++)	//inicializa vector en 0
		muestras[i]=0;
}

void ADC_IRQHandler(void){
	static uint8_t n = CANT_MUESTRAS-1;
	static uint32_t sumas = 0;
	if(ADC->CHN == 5){	//hecho con el filtro de media movil (se promedian los ultimos 10 valores)

		sumas -= muestras[n];		//cuando se hace el promedio, se le resta a la suma anterior el valor medido mas antiguo
		muestras[n] = (ADC->ADDR5 >> 4) & 0x0FFF;		//limpieza con el and y el desplazamiento porq tiene info por ahi
		sumas += muestras[n];		//sumamos el valor medido mas nuevo para

		RESULT_ADC = sumas/CANT_MUESTRAS;

		if(n)
			n--;	//un contador en base a la cantidad de muestras para promediar
		else
			n= CANT_MUESTRAS-1;

		ADC->START = 1;
	}
}
