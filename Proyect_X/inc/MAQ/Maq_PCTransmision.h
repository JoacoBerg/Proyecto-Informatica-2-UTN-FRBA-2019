#ifndef MAQ_MAQ_PCTRANSMISION_H_
#define MAQ_MAQ_PCTRANSMISION_H_

#include "PR_UART1.h"
#include "PR_Timers.h"

//-----FLAGS----------//

extern uint8_t ERROR_FLAG; //flag para avisar que hay un error
extern uint8_t START_TRANSMISION_FLAG; //flag para empezar la emision

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
#define TIMER_PC	0
#define TIMER_ERROR 1

#define TIEMPO_PC	 1 //250 milis
#define TIEMPO_ERROR 10 //segundos
void TimerHandler_ErrorPC_Reception();
void TimerHandler_Fin_De_Error();


void Maq_PCTransmision(uint8_t numero_cabina, uint8_t estado_cab);



#endif /* MAQ_MAQ_PCTRANSMISION_H_ */
