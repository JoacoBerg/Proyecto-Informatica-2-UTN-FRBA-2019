/*
 * EvalContinua4.c
 *
 *  Created on: Sep 22, 2019
 *      Author: GCRIS
 */
#include "EvalContinua4.h"

void Leds_init(uint32_t Puerto , uint32_t pin){
	GPIO_Pinsel(Puerto, pin, 0); //funcion GPIO configurada en pins
	GPIO_Mode(Puerto, pin, 0); //pull up
	GPIO_Dir(Puerto, pin, 1); //OUTPUT
}

void EvalContinua4_init()
{
    // Force the counter to be placed into memory
    InicializarPLL();
    SysTick_Init();
  //  ADC_init();
    Leds_init(PUERTO_RED , PIN_RED);
    Leds_init(PUERTO_BLUE , PIN_BLUE);
    Leds_init(PUERTO_GREEN , PIN_GREEN);
}

void (* MaquinaDeEstados[])(uint32_t*) = { Reset , F_Red_on , F_Blue_on , F_Green_on };

void EvalContinua4()
{
	static uint32_t Estado = RESET;
	MaquinaDeEstados[ Estado ]( &Estado); //puntero a funcion 'Estado' y argumento &Estado
}

// FUNCION: Reset
// param [in] uint8_t *pEstado: direccion de variable estado
// param [out] uint8_t *pEstado: modifico el valor de la variable estado
void Reset ( uint32_t *pEstado)
{
	RED_OFF;
	BLUE_OFF;
	GREEN_OFF;

	if( R < LIMITE_INF )
		*pEstado = F_RED_ON;

	if( R < LIMITE_SUP  &&  R >= LIMITE_INF )
		*pEstado = F_BLUE_ON;

	if( R >= LIMITE_SUP )
		*pEstado = F_GREEN_ON;
}

// FUNCION: Prender LED rojo
// param [in] uint8_t *pEstado: direccion de variable estado
// param [out] uint8_t *pEstado: modifico el valor de la variable estado
void F_Red_on ( uint32_t *pEstado)
{
	RED_ON;

	if( R < LIMITE_SUP  &&  R >= LIMITE_INF )
	{
		RED_OFF;
		*pEstado = F_BLUE_ON;
	}

	if( R >= LIMITE_SUP )
	{
		RED_OFF;
		*pEstado = F_GREEN_ON;
	}
}

// FUNCION: Prender Led azul
// param [in] uint8_t *pEstado: direccion de variable estado
// param [out] uint8_t *pEstado: modifico el valor de la variable estado
void F_Blue_on ( uint32_t *pEstado)
{
	BLUE_ON;

	if( R < LIMITE_INF )
	{
		BLUE_OFF;
		*pEstado = F_RED_ON;
	}

	if( R >= LIMITE_SUP )
	{
		BLUE_OFF;
		*pEstado = F_GREEN_ON;
	}
}

// FUNCION: Prender led verde
// param [in] uint8_t *pEstado: direccion de variable estado
// param [out] uint8_t *pEstado: modifico el valor de la variable estado
void F_Green_on ( uint32_t *pEstado)
{
	GREEN_ON;

	if( R < LIMITE_SUP  &&  R >= LIMITE_INF )
	{
		GREEN_OFF;
		*pEstado = F_BLUE_ON;
	}

	if( R < LIMITE_INF )
	{
		GREEN_OFF;
		*pEstado = F_RED_ON;
	}
}
