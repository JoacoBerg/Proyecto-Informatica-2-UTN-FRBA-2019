/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/
//eeee

//hola
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

// TODO: insert other include files here
#include "DR_PLL.h"
#include <DR_Systick.h>
// TODO: insert other definitions and declarations here

int main(void) {

    // TODO: insert code here

    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    InicializarPLL();
    SysTick_Init();
    // Enter an infinite loop, just incrementing a counter
    while(1) {
        i++ ;
    }
    return 0 ;
}
