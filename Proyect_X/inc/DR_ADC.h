/*
 * DR_ADC.h
 *
 *  Created on: 13 sep. 2019
 *      Author: gif30
 */
#include "DR_tipos.h"
#include "DR_PLL.h"
#include "DR_GPIO.h"

#ifndef DR_ADC_H_
#define DR_ADC_H_

#define GPIO_ADC5 1, 31


typedef struct{

	union{
		__RW uint32_t AD0CR;
		struct{
			__RW uint32_t SEL_ADC0:1;	//habilita el adc que vamos a usar
			__RW uint32_t SEL_ADC1:1;
			__RW uint32_t SEL_ADC2:1;
			__RW uint32_t SEL_ADC3:1;
			__RW uint32_t SEL_ADC4:1;
			__RW uint32_t SEL_ADC5:1;
			__RW uint32_t SEL_ADC6:1;
			__RW uint32_t SEL_ADC7:1;
			__RW uint32_t CLKDIV:8;		//sirve para setear la freq en base al PCLK
			__RW uint32_t BURST:1;
			__R uint32_t RESERVED_1:4;
			__RW uint32_t PDN:1;		//sirve para prender o apagar el modulo (bajo consumo)
			__R uint32_t RESERVED_2:2;
			__RW uint32_t START:3;
			__RW uint32_t EDGE:1;
			__RW uint32_t RESERVED_3:4;
		};
	};

	__RW uint32_t ADGR;			//en CHN podemos ver cual de los ADC interrumpio
	__R uint32_t RESERVED_0;
	union{
		__RW uint32_t ADINTEN;	//habilita la interrupcion del ADC que vamos a usar
		struct{
			__RW uint32_t ADINTEN0:1;
			__RW uint32_t ADINTEN1:1;
			__RW uint32_t ADINTEN2:1;
			__RW uint32_t ADINTEN3:1;
			__RW uint32_t ADINTEN4:1;
			__RW uint32_t ADINTEN5:1;
			__RW uint32_t ADINTEN6:1;
			__RW uint32_t ADINTEN7:1;
			__RW uint32_t ADGINTEN:1;
			__RW uint32_t RESERVED_4:23;

		};
	};

	__R uint32_t ADDR0;		//guarda el resultado de cada ADC
	__R uint32_t ADDR1;
	__R uint32_t ADDR2;
	__R uint32_t ADDR3;
	__R uint32_t ADDR4;
	__R uint32_t ADDR5;
	__R uint32_t ADDR6;
	__R uint32_t ADDR7;
	__R uint32_t ADSTAT;
	__RW uint32_t ADTRM;


}adc_t;

#define ADC ((__RW adc_t *) 0x40034000UL)


void ADC_init(void);

#endif /* DR_ADC_H_ */


