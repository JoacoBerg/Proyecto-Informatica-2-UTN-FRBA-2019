/*
 * EvalContinua4.h
 *
 *  Created on: Sep 22, 2019
 *      Author: GCRIS
 */

#ifndef EVALCONTINUA4_H_
#define EVALCONTINUA4_H_

#include "DR_PLL.h"
#include <DR_Systick.h>
#include "DR_ADC.h"
#include "DR_GPIO.h"
#include "DR_tipos.h"

//MACROS----------------------------------------------------------------------------------------
#define RESET 0
#define F_RED_ON 1
#define F_BLUE_ON 2
#define F_GREEN_ON 3
#define R resultado
#define LIMITE_INF 1000
#define LIMITE_SUP 3000

#define PUERTO_RED 0
#define PIN_RED 22
#define RED_ON GPIO_Set( 0, 22, 0)
#define RED_OFF GPIO_Set( 0 , 22, 1)

#define PUERTO_BLUE 3
#define PIN_BLUE 26
#define BLUE_ON GPIO_Set( 3, 26, 0)
#define BLUE_OFF GPIO_Set( 3, 26, 1)

#define PUERTO_GREEN 3
#define PIN_GREEN 25
#define GREEN_ON GPIO_Set( 3, 25, 0)
#define GREEN_OFF GPIO_Set( 3, 25, 1)

//funciones main--------------------------------------------------------------------------------
void EvalContinua4_init();
void EvalContinua4();
void Leds_init(uint32_t Puerto , uint32_t pin);

//void (* MaquinaDeEstados[])(uint32_t*) = { RESET , F_RED_ON , F_BLUE_ON , F_GREEN_ON };


//Estados---------------------------------------------------------------------------------------
void Reset ( uint32_t *);
void F_Red_on ( uint32_t *);
void F_Blue_on ( uint32_t *);
void F_Green_on ( uint32_t *);


#endif /* EVALCONTINUA4_H_ */
