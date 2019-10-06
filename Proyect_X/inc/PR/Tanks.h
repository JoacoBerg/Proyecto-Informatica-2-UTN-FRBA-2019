
#include "DR_PWM.h"

/* https://sites.google.com/site/angmuz/home/arduT_INo-keyes-l298-motor-driver
 * 
 * Va con PULLUP todo
 * 
 * MOTOR A    MOTOR B
 * T_ENA        T_ENB
 * T_IN1        T_IN3
 * T_IN2        T_IN4
 */


//MOTOR A
#define T_ENA PWM5  //PWM
#define T_IN1 0,11
#define T_IN2 2,0

//MOTOR B
#define T_IN3 2,1
#define T_IN4 2,2
#define T_ENB PWM4  //PWM


/* =====================================/
 * SIGNAL		|	HIGH		|	LOW				||
 * T_ENA		|	T_ENAble	|	disable			||
 * Direction 1  |	T_IN1		|	T_IN2			||
 * Direction 2  |	T_IN2		|	T_IN1			||
 * CoastT_INg	|				|	T_IN1,T_IN2		||  =~ Brake
 * Brake		|	T_IN1,T_IN2	|					||
 * ====================================*/

void Tanks_Init();
void MotorA_DirectionF(uint32_t motorSpeed);
void MotorA_DirectionB(uint32_t motorSpeed);
void MotorA_Brake();
void MotorA_Coast();
void MotorA_OFF();

void MotorB_DirectionF(uint32_t motorSpeed);
void MotorB_DirectionB(uint32_t motorSpeed);
void MotorB_Brake();
void MotorB_Coast();
void MotorB_OFF();


void Tank_OFF();
void Tank_Brake();
void Tank_Coast();

void Tank_Forward(uint32_t motorSpeed);
void Tank_Backward(uint32_t motorSpeed);
void Tank_Left(uint32_t motorSpeed);
void Tank_Right(uint32_t motorSpeed);

//void Tank_F1(uint32_t dir, uint32_t motorSpeed);
