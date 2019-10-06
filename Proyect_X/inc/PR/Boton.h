/*
 * Boton.h
 *
 *  Created on: Sep 25, 2019
 *      Author: GCRIS
 */

#ifndef BOTON_H_
#define BOTON_H_

#include <DR_PINSEL.h>
#include "DR_PLL.h"
#include <DR_Systick.h>
#include <DR_tipos.h>

#define BOTON_PORT 0
#define BOTON_PIN 24
#define BOTON GPIO_Get( BOTON_PORT, BOTON_PIN)	//lectura del GPIO

void Boton_init();

#endif /* BOTON_H_ */
