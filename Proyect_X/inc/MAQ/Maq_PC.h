/*
 * Maq_PC.h
 *
 *  Created on: Nov 28, 2019
 *      Author: GCRIS
 */

#ifndef MAQ_MAQ_PC_H_
#define MAQ_MAQ_PC_H_

#include "DR_UART1.h"
#include "PR_Maq_Recibo.h"
#include "PR_Maq_Envio.h"
#include "PR_Timers.h"

//-----FLAGS----------//
uint8_t flagERROR = 0; //si la PC no manda en 250 ms OK -> flag =1
extern uint8_t flagERROR; //si la PC no manda en 250 ms OK -> flag =1
extern uint8_t flagSEND; //solo SEND si flag = 1

//-----------MAQUINAS DE ESTADOS---------------
extern volatile uint32_t estadoRECV;

#define RESET 	0
#define SEND	1
#define RECV	2

//------ESTADOS DE CABINAS------//
#define RUN	0
#define TEP	1
#define PRE 2
#define STP	3
#define ERR	4


//----------MAQUINARIA DE TIMERS--------//
#define E_PC	0
#define E_ERROR 1

#define T_PC	250 //milisegundos
#define T_ERROR 10 //segundos
void handler_ERRORPC();
void handler_BLOCK();


 void Maquina_PC();



#endif /* MAQ_MAQ_PC_H_ */
