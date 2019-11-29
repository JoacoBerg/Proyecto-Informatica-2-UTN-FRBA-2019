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
//#include "testings.h"
#include <DR_Salidas.h>

//#include "Maq_FollowTheLine.h"
void prueba(void);
void prueba2(void);
int i = 0,a;

int main(void) {

	Inicializacion ();
	RED_OFF;
	//RED_ON;
	//GREEN_ON;
	GREEN_ON;
	//BLUE_ON;
	BLUE_ON;
	BUZZER_OFF;

	//test_Maq_GRAL_init();
   	TimerStart(1, 1, prueba, MIL);
   	while(1) {
    	TimerEvent();
    	//Maquina_PC();

    	//Maq_General();
    	//ftl();
    	//Maq_FollowTheLine_v2();
    	//test_servos();

    }

    return 0;
}


void prueba(void)
{
	//BLUE_ON;
	RED_ON;
	//GREEN_ON;
	BUZZER_ON;
	TimerStart(2, 1000, prueba2, MIL);
}

void prueba2(void)
{
	//BLUE_OFF;
	RED_OFF;
	//GREEN_OFF;
	BUZZER_OFF;
	TimerStart(1, 1000, prueba, MIL);
}

