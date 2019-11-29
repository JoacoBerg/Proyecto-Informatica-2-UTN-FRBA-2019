
/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <DR_Inicializacion.h>
#include "PR_Timers.h"
#include "PR_Display.h"
#include "PR_SE_Parcial2.h"
#include <Maq_PCTransmision.h>


#define TIMER_MAQUINA_SE		2
#define TIMER_START_SEND		3

#define TIEMPO_MAQUINA_SE	 1 //segundos
#define TIEMPO_START_SEND	 1 //250 milis

//variables Globales Main
uint8_t num_cabina = 1;
uint8_t estado_cabina = 7;

void TimerHandler_MaquinaSE(void);
void TimerHandler_StartSend(void);
void SetDisplay_Error(void);
void SetDisplay_Estado(void);

int main(void) {
	Inicializacion ();
   	TimerStart(TIMER_MAQUINA_SE, TIEMPO_MAQUINA_SE, TimerHandler_MaquinaSE, SEG);
   	Display7seg_BCD(888888);
   	SetDisplay_Estado();
   	while(1) {
    	TimerEvent();
    	Maq_PCTransmision(num_cabina, estado_cabina);
    }
    return 0;
}


void TimerHandler_MaquinaSE(void)
{
	if(num_cabina == 6)
		num_cabina = 1;
	else
		num_cabina++;
	Set_SE(num_cabina);
	TimerStart(TIMER_MAQUINA_SE, TIEMPO_MAQUINA_SE, TimerHandler_MaquinaSE, SEG);


	TimerStart(TIMER_START_SEND, TIEMPO_START_SEND, TimerHandler_StartSend, MIL250); //Este Tiempo esta para que tenga tiempo el set de la salida hecho en Set_SE()
}

void TimerHandler_StartSend(void)
{
	estado_cabina = Get_SE();
	START_TRANSMISION_FLAG = 1;
	if(ERROR_FLAG){
		SetDisplay_Error();
	}
	else{
		SetDisplay_Estado();
	}
}

void SetDisplay_Error(void){
	Display7seg_SetDigit_BCD(23, 5);
	Display7seg_SetDigit_BCD(24, 4);
	Display7seg_SetDigit_BCD(25, 3);
	Display7seg_SetDigit_BCD(26, 2);
	Display7seg_SetDigit_BCD(27, 1);
	Display7seg_SetDigit_BCD(28, 0);
}


void SetDisplay_Estado(void){
	//Set de numero de cabina
	Display7seg_SetDigit_BCD(0, 2);
	Display7seg_SetDigit_BCD(0, 1);
	Display7seg_SetDigit_BCD(num_cabina, 0);
	//Set de estado de cabina
	switch(estado_cabina){
	case ESTADO_RUN:
    	Display7seg_SetDigit_BCD(11, 5);
    	Display7seg_SetDigit_BCD(12, 4);
    	Display7seg_SetDigit_BCD(13, 3);
    break;
	case ESTADO_TEP:
    	Display7seg_SetDigit_BCD(14, 5);
    	Display7seg_SetDigit_BCD(15, 4);
    	Display7seg_SetDigit_BCD(16, 3);
    break;
	case ESTADO_PRE:
    	Display7seg_SetDigit_BCD(17, 5);
    	Display7seg_SetDigit_BCD(18, 4);
    	Display7seg_SetDigit_BCD(19, 3);
    break;
	case ESTADO_STP:
    	Display7seg_SetDigit_BCD(20, 5);
    	Display7seg_SetDigit_BCD(21, 4);
    	Display7seg_SetDigit_BCD(22, 3);
    break;
	case ESTADO_ERR:
    	Display7seg_SetDigit_BCD(23, 5);
    	Display7seg_SetDigit_BCD(24, 4);
    	Display7seg_SetDigit_BCD(25, 3);
    break;
	default:
    	Display7seg_SetDigit_BCD(23, 5);
    	Display7seg_SetDigit_BCD(24, 4);
    	Display7seg_SetDigit_BCD(25, 3);
		break;
	}
}
