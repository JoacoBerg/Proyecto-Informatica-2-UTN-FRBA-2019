/*
 * DR_Servo.h
 *
 *  Created on: 15 sep. 2019
 *      Author: Tanks
 */

#ifndef DR_SERVO_H_
#define DR_SERVO_H_

// #define SERVO_GPIO GPIO_PWM6

//la inicializacion de Servo se hace dentro de Tanks_Init() porque Tanks_Init() inicializa tambien los PWM

void Servo_Abierto(void);

void Servo_Cerrado(void);


#endif /* DR_SERVO_H_ */
