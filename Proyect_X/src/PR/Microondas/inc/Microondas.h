/*
 * Microondas.h
 *
 *  Created on: Nov 26, 2019
 *      Author: GCRIS
 */

#ifndef MICROONDAS_H_
#define MICROONDAS_H_

#include "DR_PLL.h"
#include "DR_SysTick.h"

#include "DR_UART1.h"
#include "PR_UART1.h"

#include "PR_Teclado.h"
#include "DR_tipos.h"
#include "PR_Display.h"

#include "PR_Timers.h"
#include "DR_Timers.h"

#include "DR_EXTINT.h"

#include "PR_Maq_Recibo.h"


//-----------ESTADOS-------------------
extern volatile uint8_t estado;


#define 	RESET					0
#define 	GET_TIME				1
#define 	COOK					2
#define 	COOKING					3
//------------TECLAS--------------------------
//(FILA,COLUMNA)
//(1,2) -> 1
//(1,1) -> 6
//(3,2) -> 3
//(2,1) -> 2
//(2,2) -> 5
//(3,1) -> 4
//(4,2) -> 7
/*
6	1
2	5
4	3
	7
*/
#define NIVEL_MIN	3
#define NIVEL_MED	4
#define NIVEL_MAX	5

#define SUMA		6
#define RESTA		1

#define ENCENDIDO	2
#define CANCEL		7
//-------------NIVELES DE COCCION----------------
#define Min		'1'
#define MED		'2'
#define MAX		'3'

//-----------FLAGS	-------------------
#define SLOW_SET		1
#define QUICK_SET		2
extern uint8_t flag_handler;

/*------- EVENTOS	----------	*/
#define E_COOK	 	0

/*------- TIEMPOS	----------	*/
#define T_WAIT		3

/*------- HANDLERS	----------	*/
void handler_COOK();


void IntToChar(uint32_t tiempo);

void init_microondas();
void Microondas();


#endif /* MICROONDAS_H_ */
