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
#include "DR_Servo.h"
#include "PR_Display.h"
#include "PR_Teclado.h"
// TODO: insert other definitions and declarations here

void testing_giro(void);
void testing_servos(void);
void testing_tanks(void);
void testing_tanks2(void);
void testing_ftl(void);

int main(void) {

    // TODO: insert code here

    // Force the counter to be placed into memory
	InicializarPLL();
    SysTick_Init();
    Init_Display();
    Init_Teclado();
    /*
    Tanks_Init();
    InitIR();
    Boton_init();
    */
    //Servo init no existe, ya que el tanque se encarga de eso
    while(1) {
    	uint32_t num = 0;
    	Display7seg(num);
    	switch (Lectura_Teclado ()){
			case 0:
				if (num)
					num --;
			case 1:
					num ++;

			case NO_KEY:
				break;

			default:
				break;
    	}


    	//LecturaIRs(IRx4);
    	//testing_giro();
    	//ftl();
    	//testing_ftl();
    	//testing_servos();
    	//Tank_Forward(100);
    	//testing_tanks2();
    }
    return 0 ;
}

#define TEC_1 2, 10
#define TEC_2 0, 18

teclitecla_init(void){
	SetPinsel(TEC_1, PINSEL_GPIO);
	SetPinDir(TEC_1, PINDIR_INPUT);
	SetPinMode(TEC_1, PINMODE_PULLUP);

	SetPinsel(TEC_2, PINSEL_GPIO);
	SetPinDir(TEC_2, PINDIR_INPUT);
	SetPinMode(TEC_2, PINMODE_PULLUP);
}
uint8_t teclitecla(void){
	if(LOW == GetPin(TEC_1))
		return 0;
	if(LOW == GetPin(TEC_2))
		return 1;
	return NO_KEY;
}

void testing_tanks(void){
	for(int i=0;i<500000;i++)
		Tank_Brake();
	for(int i=0;i<500000;i++)
		Tank_Left(100);
	for(int i=0;i<500000;i++)
		Tank_Right(100);
	for(int i=0;i<500000;i++)
		Tank_Forward(100);
	for(int i=0;i<500000;i++){
		MotorA_Brake();
		MotorB_DirectionF(100);
	}
	for(int i=0;i<500000;i++){
		MotorB_Brake();
		MotorA_DirectionF(100);
	}
}

void testing_tanks2(void){
	for(int i=0;i<500000;i++)
		Tank_Brake();
	for(int i=0;i<500000;i++)
		Tank_Forward(100);
	for(int i=0;i<500000;i++)
		Tank_Backward(100);


}



void testing_servos(void){
	for(int i=0;i<500000;i++)
		Servo_Abierto();
	for(int i=0;i<500000;i++)
	    Servo_Cerrado();
}

void testing_giro(void){
	static int i=0;
   	if( i == 0){
   		if(Maq_Giro(IZQ))
   			i = 1;
   	}
    else if(i == 1){
    	for(uint32_t i=0;i<5000000;i++){}
    		i = 0;
    }
}


void testing_ftl(void){
	static int i=0;
   	if( i == 0){
   		if(Maq_FollowTheLine())
   			i = 1;
   	}
    else if(i == 1){
    	for(uint32_t i=0;i<50000000;i++){}
    		i = 0;
    }
}
