/*
===============================================================================
 Name        : Microondas.c
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
#include "Microondas.h"

int main(void) {

	init_microondas();

	INFO_RED_OFF;
	INFO_GREEN_OFF;
	INFO_BLUE_OFF;
	BUZZER_OFF;
	while(1){

		TimerEvent();
		Microondas();
		Maq_Recibo();

	}
}
