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
// TODO: insert other definitions and declarations here

int main(void) {

	EvalContinua4_init();

	while(1)
	{
		EvalContinua4();
	}
	

    return 0;
}
