#include "Tanks.h"
#include "DR_GPIO.h"

//========================== MOTOR A
void Tanks_Init(){

	PWM_Init();

	SetPinsel(T_IN1, PINSEL_GPIO);
	SetPinMode(T_IN1,PINMODE_PULLUP);
	SetPinDir(T_IN1,OUTPUT);

	SetPinsel(T_IN2, PINSEL_GPIO);
	SetPinMode(T_IN2,PINMODE_PULLUP);
	SetPinDir(T_IN2,OUTPUT);


	SetPinsel(T_IN3, PINSEL_GPIO);
	SetPinMode(T_IN3,PINMODE_PULLUP);
	SetPinDir(T_IN3,OUTPUT);
    
	SetPinsel(T_IN4, PINSEL_GPIO);
	SetPinMode(T_IN4,PINMODE_PULLUP);
	SetPinDir(T_IN4,OUTPUT);

	Tank_OFF();
}

//========================== MOTOR A

void MotorA_DirectionB(uint32_t motorSpeed){
	updatePulseWidth(T_ENA, (motorSpeed*PWM_DIVISOR)/100);
	SetPin(T_IN1, LOW);
	SetPin(T_IN2, HIGH);
}

void MotorA_DirectionF(uint32_t motorSpeed){
	updatePulseWidth(T_ENA, (motorSpeed*PWM_DIVISOR)/100);
	SetPin(T_IN1, HIGH);
	SetPin(T_IN2, LOW);
}

void MotorA_Brake(){
	updatePulseWidth(T_ENA, PWM_DIVISOR);
	SetPin(T_IN1, HIGH);
	SetPin(T_IN2, HIGH);
}

void MotorA_Coast(){
	updatePulseWidth(T_ENA, PWM_DIVISOR);
	SetPin(T_IN1, LOW);
	SetPin(T_IN2, LOW);
}

void MotorA_OFF(){
	updatePulseWidth(T_ENA, OFF);
}





//========================== MOTOR B

void MotorB_DirectionB(uint32_t motorSpeed){
	updatePulseWidth(T_ENB, (motorSpeed*PWM_DIVISOR)/100);
	SetPin(T_IN3, LOW);
	SetPin(T_IN4, HIGH);
}

void MotorB_DirectionF(uint32_t motorSpeed){
	updatePulseWidth(T_ENB, (motorSpeed*PWM_DIVISOR)/100);
	SetPin(T_IN3, HIGH);
	SetPin(T_IN4, LOW);
}

void MotorB_Brake(){
	updatePulseWidth(T_ENB, PWM_DIVISOR);
	SetPin(T_IN3, HIGH);
	SetPin(T_IN4, HIGH);
}

void MotorB_Coast(){
	updatePulseWidth(T_ENB, PWM_DIVISOR);
	SetPin(T_IN3, LOW);
	SetPin(T_IN4, LOW);
}

void MotorB_OFF(){
	updatePulseWidth(T_ENB, OFF);
}





//==========================Tank

void Tank_OFF(){
  MotorA_OFF();
  MotorB_OFF();
}

void Tank_Brake(){
  MotorA_Brake();
  MotorB_Brake();
}

void Tank_Coast(){
  MotorA_Coast();
  MotorB_Coast();
}

void Tank_Forward(uint32_t motorSpeed){
  MotorA_DirectionF(motorSpeed);
  MotorB_DirectionF(motorSpeed);
}

void Tank_Backward(uint32_t motorSpeed){
  MotorA_DirectionB(motorSpeed);
  MotorB_DirectionB(motorSpeed);
}

void Tank_Left(uint32_t motorSpeed){
  MotorA_DirectionF(motorSpeed);
  MotorB_DirectionB(motorSpeed);
}

void Tank_Right(uint32_t motorSpeed){
  MotorA_DirectionB(motorSpeed);
  MotorB_DirectionF(motorSpeed);
}
