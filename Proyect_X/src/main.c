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

// TODO: insert other include files here
#include "DR_PLL.h"
#include "Tanks.h"
#include "DR_IR.h"
#include <DR_Systick.h>
#include <Maq_FollowTheLine.h>
#include "Maq_Giro.h"
#include "Boton.h"
// TODO: insert other definitions and declarations here


int main(void) {

    // TODO: insert code here

    // Force the counter to be placed into memory
    InicializarPLL();
    SysTick_Init();
    Tanks_Init();
    InitIR();
    Boton_init();

    while(1) {
    	int i=0;
    	//LecturaIRs(IRx4);
        if(i == 1){
        	if(Maq_FollowTheLine())
        		i = 2;
        }
       	else if( i == 0){
       		if(Maq_Giro(IZQ))
       			i = 1;
       	}
        else if(i == 2){
        	if(BOTON)
        		i = 0;
        }
    }

    return 0 ;
}
