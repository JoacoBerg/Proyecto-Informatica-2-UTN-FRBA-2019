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
#include "DR_Servo.h"

void test_servos(void);

int main(void) {

   	Inicializacion ();
   	Servo_Cerrado();


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


void test_servos(void){
	static uint8_t a = 0;

	if (Maq_Dummy()){
		if(a == 0){
			Servo_Abierto();
			a = 1;
		}
		else{
			Servo_Cerrado();
			a = 0;
		}
	}
}
