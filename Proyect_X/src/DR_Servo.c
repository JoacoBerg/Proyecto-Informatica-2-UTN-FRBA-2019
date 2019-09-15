/*
 * DR_Servo.c
 *
 *  Created on: 15 sep. 2019
 *      Author: gif30
 */
#include "DR_PWM.h"
#define SERVO PWM6

void Servo_Abierto(void){
	updatePulseWidth(SERVO, (PWM_DIVISOR/20)*2);
}
void Servo_Cerrado(void){
	updatePulseWidth(SERVO, PWM_DIVISOR/20);
}
