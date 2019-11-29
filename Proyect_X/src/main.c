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
//void prueba2(void);

uint8_t num_cabina = 1;
uint8_t estado_cabina = 0;

int main(void) {
	Inicializacion ();
	//test_Maq_GRAL_init();
   	TimerStart(2, 1, tiempo_pregunta, SEG);
   	Display7seg_BCD(000000);
   	while(1) {
    	TimerEvent();
    	Maquina_PC();
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
	Get_SE(num_cabina);
	TimerStart(2, 1, tiempo_pregunta, SEG);
	TimerStart(3, 1, tiempo_seteos, MIL250);
}

void tiempo_seteos(void)
{
	flagSend = 1;
	if(flagError){
    	Display7seg_per_digit_BCD(4, 0);
    	Display7seg_per_digit_BCD(4, 1);
    	Display7seg_per_digit_BCD(4, 2);
    	Display7seg_per_digit_BCD(4, 3);
    	Display7seg_per_digit_BCD(4, 4);
    	Display7seg_per_digit_BCD(4, 5);
	}
}
