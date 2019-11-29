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
#include "PR_Display.h"

//#include "Maq_FollowTheLine.h"
void prueba(void);
void prueba2(void);
int i = 0,a;

int main(void) {

	Inicializacion ();
	//RED_OFF;
	RED_ON;
	//GREEN_ON;
	//GREEN_OFF;
	//BLUE_ON;
	//BLUE_OFF;
	BUZZER_ON;

	//test_Maq_GRAL_init();
   	TimerStart(1, 1, prueba, SEG);
   	while(1) {
    	TimerEvent();
    	//Maq_General();
    	//ftl();
    	//Maq_FollowTheLine_v2();
    	//test_servos();
    	Display7seg_BCD(123456);


    }

    return 0;
}


void prueba(void)
{
	BLUE_ON;
	//RED_ON;
	//GREEN_ON;
	TimerStart(2, 1, prueba2, SEG);
}

void prueba2(void)
{
	BLUE_OFF;
	//RED_OFF;
	//GREEN_OFF;
	TimerStart(1, 1, prueba, SEG);
}

