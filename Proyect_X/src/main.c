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

#include "DR_PLL.h"
#include "Tanks.h"
#include "DR_IR.h"
#include "DR_Systick.h"
#include "Maq_FollowTheLine.h"
#include "Maq_Giro.h"
#include "DR_Servo.h"
#include "DR_Inicializacion.h"
#include "DR_Timers.h"
#include "PR_Timers.h"
#include "Maq_GRAL.h"
#include "DR_GPIO.h"
#include "DR_PINSEL.h"

void testing_giro(void);
void testing_servos(void);
void testing_tanks(void);
void testing_tanks2(void);
void testing_ftl(void);
void testing_ftl_giro(void);

void hand(void);
void hand2(void);

#define RES 0
#define FTL 1
#define GIR 2
#define NADA 3

int flagT = 0;
uint8_t est = RES;



int main(void) {

   	Inicializacion ();


    while(1) {
    	//testing();
    	TimerEvent();
    	ftl(); // hace que el auto siga una linea negra
    	Maq_General();

    	//testing_ftl();//esta maquina hace que cuando detecta un cruce frene y devuelva exito, y vuelva a arrancar
    	//testing_ftl_giro();
    	//Maq_FollowTheLine();
    	//testing_servos();
    	//testing_tanks2();
    }
    return 0 ;
}

void testing_ftl(void)
{

	if(flagT == 0)
	{
		//if(Maq_FollowTheLine_v2() == EXITO)
		if(Maq_Giro(DER) == EXITO)
		{
			flagT = 1;
			TimerStart(2, 3, hand2, SEG);
		}
	}
}

void hand2(void)
{
	flagT = 0;
}


void testing_ftl_giro(void)
{
	int j = 0, y = 0;

	switch(est)
	{
		case RES:
			est = FTL;
			Flag_Control = ON;
			break;

		case FTL:
			j = Maq_FollowTheLine_v2();
			if(j == EXITO)
			{
				est = GIR;
				Flag_Control = OFF;
			}
			break;

		case GIR:
			Maq_Giro(DER);
			if(y == EXITO)
			{
				est = RES;
			}
			break;

		case NADA:
			break;
	}
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



