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
#include "Maq_PC.h"

//#include "Maq_FollowTheLine.h"
void tiempo_pregunta(void);
void tiempo_seteos(void);
//void prueba2(void);

uint8_t num_cabina = 1;
uint8_t estado_cabina = 0;

int main(void) {
	Inicializacion ();
	//test_Maq_GRAL_init();
   	TimerStart(2, 1, tiempo_pregunta, SEG);
   	Display7seg_BCD(888888);
   	while(1) {
    	TimerEvent();
    	Maquina_PC(num_cabina, estado_cabina);
    	//Display7seg_BCD(000000);

    }
    return 0;
}


void tiempo_pregunta(void)
{
	if(num_cabina == 6)
		num_cabina = 1;
	else
		num_cabina++;
	Set_SE(num_cabina);
	TimerStart(2, 1, tiempo_pregunta, SEG);


	TimerStart(3, 1, tiempo_seteos, MIL250); //Este Tiempo esta para que tenga tiempo el set de la salida hecho en Set_SE()
}

void tiempo_seteos(void)
{
	estado_cabina = Get_SE();
	flagSEND = 1;
	if(flagERROR){
    	Display7seg_per_digit_BCD(23, 0);
    	Display7seg_per_digit_BCD(24, 1);
    	Display7seg_per_digit_BCD(25, 2);
    	Display7seg_per_digit_BCD(26, 3);
    	Display7seg_per_digit_BCD(27, 4);
    	Display7seg_per_digit_BCD(28, 5);
	}
	else{
		//Set de numero de cabina
    	Display7seg_per_digit_BCD(0, 2);
    	Display7seg_per_digit_BCD(0, 1);
    	Display7seg_per_digit_BCD(num_cabina, 0);
    	//Set de estado de cabina
		switch(estado_cabina){
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
