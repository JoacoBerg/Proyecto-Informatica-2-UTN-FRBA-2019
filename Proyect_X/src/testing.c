/*
 * testing.c
 *
 *  Created on: 10 nov. 2019
 *      Author: gif30
 */

#include <PR_Servo.h>
#include "Maq_GRAL.h"
#include "PR_Timers.h"
#include "Maq_FollowTheLine.h"
#include "DR_GPIO.h"

void test_Maq_GRAL_init(void){

	   	Push_list_estados(FORWARD);
	   	Push_list_estados(FORWARD);
	   	Push_list_estados(FRENO);

	   	Push_list_estados(GIRO_DER);
	   	Push_list_estados(FORWARD);
	   	Push_list_estados(FRENO);
	   	Push_list_estados(CAJA);

	   	Push_list_estados(GIRO_DER);
	   	Push_list_estados(GIRO_DER);
	   	Push_list_estados(FORWARD);
	   	Push_list_estados(FRENO);

	   	Push_list_estados(GIRO_IZQ);
	   	Push_list_estados(FORWARD);
	   	//Push_list_estados(FORWARD);
	   	Push_list_estados(FRENO);
}

void test_servos(void){
	static uint8_t a = 0;

	if (Maq_Dummy()){
		if(a == 0){
			Servo_Abierto();
			a = 1;
		}
		else{
			Servo_Cerrado();
			a = 0;
		}
	}
}

void test_leds(void){
	static uint8_t a = 0;

	if (Maq_Dummy()){
		if(a == 0){
			SetPin(2,6, ON);
			a = 1;
		}
		else{
			SetPin(2,6, OFF);
			a = 0;
		}
	}
}
