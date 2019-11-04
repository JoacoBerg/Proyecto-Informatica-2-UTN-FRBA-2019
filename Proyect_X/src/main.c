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
#include "BUFFER_MAQ.h"

void testing_giro(void);
void testing_servos(void);
void testing_tanks(void);
void testing_tanks2(void);
void testing_ftl(void);
void testing_ftl_giro(void);

int main(void) {

   	Inicializacion ();
   	//int t = 0;

   	//for testing
   //Push_list_estados(FORWARD);
   	//Push_list_estados(FORWARD);
   	Push_list_estados(FORWARD);
   	Push_list_estados(FORWARD);
   	Push_list_estados(GIRO_DER);
   	Push_list_estados(FORWARD);
   	Push_list_estados(GIRO_DER);
   	Push_list_estados(GIRO_DER);
   	Push_list_estados(FORWARD);
   	Push_list_estados(GIRO_IZQ);
   	Push_list_estados(FORWARD);
   	Push_list_estados(FORWARD);


   	//Push_list_estados(GIRO_DER);
   	//Push_list_estados(FORWARD);

   	while(1) {
    	TimerEvent();
    	Maq_General();

    	/*
    	switch(t){

    		case(0):
				ftl();
				if(Maq_FollowTheLine_v2()== EXITO)
					t++;
    			break;

    		case(1):
				if(Maq_Giro_v2(DER)== EXITO)
					t++;
    			break;

    		case(2):
				ftl();
				if(Maq_FollowTheLine_v2()== EXITO)
					t++;
    			break;

    		case(3):
				if(Maq_Giro_v2(IZQ)== EXITO)
					t++;
    			break;

    		default:
    			break;
    	}*/
    }

    return 0;
}





/*
void testing_ftl(void)
{
	int i = 0;

	if(i == 0)
	{
		Flag_Control_G = 1;
		i = 1;
	}

	if(Maq_Giro_v2(DER) == EXITO)
	{
		Flag_Control_G = 0;
		if(j == 0)
		{
			TimerStart(2, 3, hand2, SEG);
			j = 1;
		}

	}
////////////////////////////////
	if(Flag_Control_G == 1)
	{
		//if(Maq_FollowTheLine_v2() == EXITO)

	}
}*/

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



