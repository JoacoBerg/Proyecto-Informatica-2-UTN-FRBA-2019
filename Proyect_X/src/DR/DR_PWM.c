/*******************************************************************************************************************************//**
 *
 * @file		DR_PWM1.c
 * @brief		Descripcion del modulo
 * @date		8 sep. 2019
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <DR_PWM.h>

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/
/**
	\fn  Nombre de la Funcion
	\brief Descripcion
 	\author Ing. Marcelo Trujillo
 	\date 8 sep. 2019
 	\param [in] parametros de entrada
 	\param [out] parametros de salida
	\return tipo y descripcion de retorno
*/

void PWM_Init(void)
{
	/*Assuming that PLL0 has been setup with CCLK = 100Mhz and PCLK = 25Mhz.*/


	PCONP |= (1<<6); 				// PowerPWM (PCPWM1 == 6)



	PCLKSEL0 &= ~(3<<12);			// Borrar lo que haya ecrito ahi
	//PCLKSEL0 |= (1<<12);			// PCLK_peripheral = CCLK


	PWM->PWM1PR = PWMPRESCALE;		/* Prescalar */


	PWM->PWM1MR0 = PWM_DIVISOR; 	//1000us = 1ms period duration 	//PWM_DIVISOR de todos
	PWM->PWMMR0R = 1;				// Reset PWM TC on PWM1MR0 match

	// update values in MR0
	PWM->LER_ENA0 = 1;

	//enable counters and PWM Mode
	PWM->TCR_PWMENA = 1;
	PWM->TCR_CountENA = 1;

	// Y PWM->PWMSEL1???  			//no tiene modo double edge el PWM1.1
	//PWM->PWMSEL2 = 0;				// Select Single Edge PWM
	//PWM->PWMSEL3 = 0;
	PWM->PWMSEL4 = 0;
	PWM->PWMSEL5 = 0;
	PWM->PWMSEL6 = 0;

	//updatePulseWidth(PWM1,OFF);
	//updatePulseWidth(PWM2,OFF);
	//updatePulseWidth(PWM3,OFF);
	updatePulseWidth(PWM4,OFF);
	updatePulseWidth(PWM5,OFF);
	updatePulseWidth(PWM6,OFF);

	// enable PWM OUTPUT (desde el modulo de hardware de PWM)
	//PWM->PWMENA1 = 1;
	//PWM->PWMENA2 = 1;
	//PWM->PWMENA3 = 1;
	PWM->PWMENA4 = 1;
	PWM->PWMENA5 = 1;
	PWM->PWMENA6 = 1;
	

	//GPIO_Pinsel(GPIO_PWM1, PINSEL_FUNC1); 			//PWM1
	//GPIO_Pinsel(GPIO_PWM2, PINSEL_FUNC1);				//PWM2
	//GPIO_Pinsel(GPIO_PWM3, PINSEL_FUNC1);				//PWM3
	SetPinsel(GPIO_PWM4, PINSEL_FUNC1);				//PWM4
	SetPinsel(GPIO_PWM5, PINSEL_FUNC1);				//PWM5
	SetPinsel(GPIO_PWM6, PINSEL_FUNC1);				//PWM6
}


void updatePulseWidth(uint8_t num, uint32_t pulseWidth)
{
	switch(num){

		case PWM1:
			PWM->PWM1MR1 = pulseWidth;	//Update MR1 with new value
			PWM->LER_ENA1 = 1;			//Load the MR1 new value at start of next cycle
			break;

		case PWM2:
			PWM->PWM1MR2 = pulseWidth;
			PWM->LER_ENA2 = 1;
			break;

		case PWM3:
			PWM->PWM1MR3 = pulseWidth;
			PWM->LER_ENA3 = 1;
			break;

		case PWM4:
			PWM->PWM1MR4 = pulseWidth;
			PWM->LER_ENA4 = 1;
			break;

		case PWM5:
			PWM->PWM1MR5 = pulseWidth;
			PWM->LER_ENA5 = 1;
			break;

		case PWM6:
			PWM->PWM1MR6 = pulseWidth;
			PWM->LER_ENA6 = 1;
			break;

		default:
			break;
	}
}
