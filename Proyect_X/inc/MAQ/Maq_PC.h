#ifndef MAQ_MAQ_PC_H_
#define MAQ_MAQ_PC_H_

#include "DR_UART1.h"
#include "PR_Maq_Recibo.h"
#include "PR_Maq_Envio.h"
#include "PR_Timers.h"

//-----FLAGS----------//

extern uint8_t flagERROR; //flag para avisar que hay un error
extern uint8_t flagSEND; //flag para empezar la emision

//-----------MAQUINAS DE ESTADOS---------------

#define RESET   	0
#define SENDUNG	    1
#define RECEPTION	2

//------ESTADOS DE CABINAS------//
#define ESTADO_RUN	7
#define ESTADO_TEP	1
#define ESTADO_PRE  2
#define ESTADO_STP	3
#define ESTADO_ERR	4


//----------MAQUINARIA DE TIMERS--------//
#define E_PC	0
#define E_ERROR 1

#define TIEMPO_PC	 1 //250 milis
#define TIEMPO_ERROR 10 //segundos
void TimerHandler_ErrorPC_Reception();
void TimerHandler_Fin_De_Error();


void Maq_PCTransmision(uint8_t NUM_CABINA, uint8_t ESTADO);



#endif /* MAQ_MAQ_PC_H_ */
