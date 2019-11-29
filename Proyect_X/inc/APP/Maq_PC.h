#ifndef APP_MAQ_PC_H_
#define APP_MAQ_PC_H_

#include "DR_UART1.h"
#include "PR_UART1.h"
#include "PR_Timers.h"

//-----FLAGS----------//

extern uint8_t flagERROR; //si la PC no manda en 250 ms OK -> flag =1
extern uint8_t flagSEND; //solo SEND si flag = 1

//-----------MAQUINAS DE ESTADOS---------------

#define RESET 	0
#define SEND	1
#define RECV	2

//------ESTADOS DE CABINAS------//
#define RUN_e	7
#define TEP	1
#define PRE 2
#define STP	3
#define ERR	4


//----------MAQUINARIA DE TIMERS--------//
#define E_PC	0
#define E_ERROR 1

#define T_PC	1 //milisegundos
#define T_ERROR 10 //segundos
void handler_ERRORPC();
void handler_BLOCK();


void Maquina_PC(uint8_t NUM_CABINA, uint8_t ESTADO);



#endif
