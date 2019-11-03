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

#include "DR_SPI.h"

#include "DR_PLL.h"
#include <DR_Systick.h>
#include "DR_GPIO.h"
#include "DR_tipos.h"
//#include "DR_SPI_MFRC522.h"
#include "EvalContinua4.h"
//#include "Boton.h"

//#include <stdio.h>
#include <PR_MFRC522.h>
#include <PR_SPI.h>
int main() {

  // setup does initial pin config, performs a soft reset on the card, and sets
  // some sane defaults for the SunFounder Mifare RC522 card
	  setup_SPI();
	setup_MFRC522();
  EvalContinua4_init();
  BLUE_OFF;
  GREEN_OFF;
  RED_OFF;

  while(1) {

	  if( Card())
		  RED_ON;
	  else
		  { BLUE_OFF;
	  	  GREEN_OFF;
	  	  RED_OFF;}

	  for(int i = 0; i<100000000;i++);
  }

  return(0);
}


/*
int main(void) {

 InicializarPLL();
  //  SysTick_Init();
    SPI_init();


    while(1){
    	SPI_ChipSelect_LOW();
    	SPI_Write('9');
    	SPI_Read();
    }

return 0;}
*/
/*
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
}*/

