
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
#include "SistExt.h"
#include "Maq_PC.h"


void handler_preguntar(void);
void handler_set(void);

uint8_t cab_est = 0;
uint8_t cab_num = 1;


int main(void) {

	Inicializacion (); //Inicializo todo lo pedido

   	TimerStart(2, 1, handler_preguntar, SEG); //Impresion en los displays de 7 Segmentos + Sistema externo

   	Display7seg_BCD(888888); //Prendo todos los D7s en 8

   	while(1) {

    	TimerEvent(); //Maquina de timers

    	Maquina_PC(cab_num, cab_est); //Maquina de comunicacion por uart

    }
    return 0;
}


void handler_preguntar(void)
{
	if(cab_num == 6)
		cab_num = 1;
	else
		cab_num++;
	Set_SE(cab_num);
	TimerStart(2, 1, handler_preguntar, SEG);
	TimerStart(3, 1, handler_set, MILISX250);
}


void handler_set(void)
{
	cab_est = Get_SE();
	flagSEND = 1;

	//Print error con PC
	if(flagERROR){
    	Display7seg_per_digit_BCD(23, 0);
    	Display7seg_per_digit_BCD(24, 1);
    	Display7seg_per_digit_BCD(25, 2);
    	Display7seg_per_digit_BCD(26, 3);
    	Display7seg_per_digit_BCD(27, 4);
    	Display7seg_per_digit_BCD(28, 5);
	}
	else{
		//Print del numro de cabina
    	Display7seg_per_digit_BCD(0, 1);
    	Display7seg_per_digit_BCD(0, 2);
    	Display7seg_per_digit_BCD(cab_num, 0);

    	//Print estado de cabina
		switch(cab_est){
		case RUN_e:
	    	Display7seg_per_digit_BCD(11, 5);
	    	Display7seg_per_digit_BCD(12, 4);
	    	Display7seg_per_digit_BCD(13, 3);
	    break;
		case TEP:
	    	Display7seg_per_digit_BCD(14, 5);
	    	Display7seg_per_digit_BCD(15, 4);
	    	Display7seg_per_digit_BCD(16, 3);
	    break;
		case PRE:
	    	Display7seg_per_digit_BCD(17, 5);
	    	Display7seg_per_digit_BCD(18, 4);
	    	Display7seg_per_digit_BCD(19, 3);
	    break;
		case STP:
	    	Display7seg_per_digit_BCD(20, 5);
	    	Display7seg_per_digit_BCD(21, 4);
	    	Display7seg_per_digit_BCD(22, 3);
	    break;
		case ERR:
	    	Display7seg_per_digit_BCD(23, 5);
	    	Display7seg_per_digit_BCD(24, 4);
	    	Display7seg_per_digit_BCD(25, 3);
	    break;
		}
	}
}
