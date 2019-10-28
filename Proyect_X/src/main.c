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
#include "DR_Inicializacion.h"
#include "DR_Timers.h"
#include "PR_Timers.h"
// TODO: insert other definitions and declarations here

void testing_giro(void);
void testing_servos(void);
void testing_tanks(void);
void testing_tanks2(void);
void testing_ftl(void);

int main(void) {

   	Inicializacion ();

    //Servo init no existe, ya que el tanque se encarga de eso
    while(1) {
    	//testing();

    	TimerEvent();
    	//Flag_Control = 1;



    	ftl(); // hace que el auto siga una linea negra
    	testing_ftl(); //aca esta la maquina de estados que estoy probando (que ademas prende y apaga la maquina que esta arriba --> ftl())
    				   //esta maquina hace que cuando detecta un cruce frene y devuelva exito, y vuelva a arrancar





    	//Maq_FollowTheLine();
    	//testing_servos();
    	//Tank_Forward(100);
    	//testing_tanks2();

    	//Tank_Forward(80);
    	//TimerStart(1, 3, TimerFrenar, SEG);
    	//TimerClose();

    }
    return 0 ;
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

	Flag_MFTL2 = ON;
	int j = Maq_FollowTheLine_v2(); //detecta cruces
   	if(j == EXITO)
   		i = 1;

    if(i == 1){
    	Flag_MFTL2 = OFF;
    	for(uint32_t i=0;i<50000000;i++){}
    		i = 0;
    }
}
