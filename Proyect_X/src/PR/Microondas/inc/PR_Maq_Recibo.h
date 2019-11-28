/*
 * PR_Maq_Recibo.h
 *
 *  Created on: Nov 10, 2019
 *      Author: GCRIS
 */

#ifndef PR_MAQ_RECIBO_H_
#define PR_MAQ_RECIBO_H_

#include "PR_UART1.h"
#include "DR_tipos.h"
#include "PR_Display.h"

#include "PR_Timers.h"
#include "DR_Timers.h"

#include "Microondas.h"
#include "DR_Salidas.h"

//---------EVENTOS--------------
#define E_DESCONTAR1		1
#define E_DESCONTAR2		2

//---------TIEMPOS--------------
#define T_DESCONTAR1		1
#define T_DESCONTAR2		1

//---------HANDLERS-------------
void handler_Descontar1();
void handler_Descontar2();

//--------VARIABLES GLOBALES------
extern volatile int Level, tempo;
extern volatile int flag_Cooking;//no cocinando hasta que flag = 1
extern volatile int flagDesc; //una sola vez llamo a TimerStart, despues se arregla


void Maq_Recibo();

#endif /* PR_MAQ_RECIBO_H_ */
