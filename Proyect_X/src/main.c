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
void prueba(void);
void prueba2(void);
int i = 0,a;

int main(void) {

   	Inicializacion ();
   	//test_Maq_GRAL_init();
   	TimerStart(1, 1, prueba, MIL);
   	while(1) {
    	TimerEvent();
    	//Maq_General();
    	//ftl();
    	//Maq_FollowTheLine_v2();
    	//test_servos();
    	if(i == 10000)
    	{
    		a++;
    	}

    }

    return 0;
}


void prueba(void)
{
	i++;
	TimerStart(2, 1, prueba2, MIL);
}

void prueba2(void)
{
	i++;
	TimerStart(1, 1, prueba, MIL);
}

