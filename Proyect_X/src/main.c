/*
===============================================================================
 Name        : main.c
 Author      : $(Tanks)
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
//#include "Maq_GRAL.h"
#include "MAQ_Alarmas.h"

#include "DR_GPIO.h"
#include "DR_PINSEL.h"

#include "testings.h"

#include "Maq_FollowTheLine.h"

#define LED1 2,6
#define LED2 2,7
#define LED3 2,8
#define LED4 2,10

int main(void) {

   	Inicializacion ();
   	//test_Maq_GRAL_init();


   	SetPinsel(LED1, PINSEL_GPIO);
	SetPinMode(LED1, PINMODE_PULLUP);
	SetPinDir(LED1, PINDIR_OUTPUT);

	SetPinsel(LED2, PINSEL_GPIO);
	SetPinMode(LED2, PINMODE_PULLUP);
	SetPinDir(LED2, PINDIR_OUTPUT);

	SetPinsel(LED3, PINSEL_GPIO);
	SetPinMode(LED3, PINMODE_PULLUP);
	SetPinDir(LED3, PINDIR_OUTPUT);

	SetPinsel(LED4, PINSEL_GPIO);
	SetPinMode(LED4, PINMODE_PULLUP);
	SetPinDir(LED4, PINDIR_OUTPUT);


	SetPin(LED1, ON);
	SetPin(LED2, ON);
	SetPin(LED3, ON);
	SetPin(LED4, ON);

	SetPin(LED1, OFF);
	SetPin(LED2, OFF);
	SetPin(LED3, OFF);
	SetPin(LED4, OFF);

   	while(1) {
    	TimerEvent();

    	//Maq_General();
    	Maq_Alarma();

    	//Flag_Turn_ftl = ON;
    	//ftl_Alarma();
    	//ftl();
    	//Maq_FollowTheLine_v2();
    	//test_servos();

   		//test_leds();


    }

    return 0;
}


