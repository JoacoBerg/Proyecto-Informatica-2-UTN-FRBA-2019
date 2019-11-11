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
#include "Maq_GRAL.h"
//#include "testings.h"

//#include "Maq_FollowTheLine.h"

int main(void) {

   	Inicializacion ();
   	//test_Maq_GRAL_init();

   	while(1) {
    	TimerEvent();
    	Maq_General();
    	//ftl();
    	//Maq_FollowTheLine_v2();
    	//test_servos();
    }

    return 0;
}


