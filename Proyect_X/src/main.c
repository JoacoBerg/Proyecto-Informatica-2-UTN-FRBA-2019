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

#include "DR_Inicializacion.h"
#include "PR_Timers.h"
#include "Maq_GRAL.h"

int main(void) {

   	Inicializacion ();

/*
   	Push_list_estados(FORWARD);
   	Push_list_estados(FORWARD);
   	Push_list_estados(FRENO);

   	Push_list_estados(GIRO_DER);
   	Push_list_estados(FORWARD);
   	Push_list_estados(FRENO);
   	Push_list_estados(CAJA);
   	Push_list_estados(GIRO_DER);
   	Push_list_estados(GIRO_DER);
   	Push_list_estados(FORWARD);
   	Push_list_estados(FRENO);
   	Push_list_estados(GIRO_IZQ);
   	Push_list_estados(FORWARD);
   	//Push_list_estados(FORWARD);
   	Push_list_estados(FRENO);
*/

   	while(1) {
    	TimerEvent();
    	Maq_General();
    }

    return 0;
}
