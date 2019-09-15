/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

//hola
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

// TODO: insert other include files here
#include "DR_PLL.h"
#include "Tanks.h"
#include "DR_IR.h"
#include <DR_Systick.h>
// TODO: insert other definitions and declarations here
#define SERVO PWM6

int main(void) {

    // TODO: insert code here

    // Force the counter to be placed into memory
    InicializarPLL();
    SysTick_Init();
    Tanks_Init();
    InitIR();


    while(1) {

    	Mfollowtheline();



    	/*
    	updatePulseWidth(SERVO, PWM_DIVISOR/20);
    	for(int i=0;i<5000000;i++){}
    	updatePulseWidth(SERVO, (PWM_DIVISOR/20)*2);
    	for(int i=0;i<5000000;i++){}


		for (int i=0;i<500000;i++){
			//Tank_OFF(PWM_DIVISOR);
			Tank_Forward(750);
		}
		for (int i=0;i<500000;i++){
			Tank_Forward(PWM_DIVISOR);
		}
		for (int i=0;i<500000;i++){
			Tank_Brake();
		}
		for (int i=0;i<500000;i++){
			Tank_Left(PWM_DIVISOR);
		}
		for (int i=0;i<500000;i++){
			Tank_Right(PWM_DIVISOR);
		}
		for (int i=0;i<500000;i++){
			Tank_Coast(PWM_DIVISOR);
		}
	*/
    }
    return 0 ;
}
