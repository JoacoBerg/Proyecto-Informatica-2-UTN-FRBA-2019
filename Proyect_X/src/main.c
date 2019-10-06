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
#include "EvalContinua4.h"
#include "Boton.h"
// TODO: insert other definitions and declarations here

int main(void) {

	EvalContinua4_init();
	Boton_init();
BLUE_OFF;
GREEN_OFF;
RED_OFF;
	while(1)
	if(BOTON)
	{
		RED_ON;
	}
	else
		RED_OFF;

    return 0 ;
		EvalContinua4();
    return 0;
}
