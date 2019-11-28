/*******************************************************************************************************************************//**
 *
 * @file		DR_Salidas.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		14 de nov. de 2017
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef DRIVERS_INFOTRONIC_INC_DR_SALIDAS_H_
#define DRIVERS_INFOTRONIC_INC_DR_SALIDAS_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "DR_tipos.h"
#include "DR_PINSEL.h"
#include "DR_GPIO.h"
/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/
#define		OUT0			2,0 	//rel 2
#define		OUT1			0,23	//rel 3
#define		OUT2			0,21 	//rel 1
#define		OUT3			0,27
#define 	OUT_BUZZER		0,28

//LEDs de Placa Infotronic
#define		INFOTRONIC_BLUE			2,1
#define		INFOTRONIC_GREEN		2,2
#define		INFOTRONIC_RED			2,3

#define INFO_BLUE_ON		SetPin ( INFOTRONIC_BLUE , ON) //AZUL
#define INFO_GREEN_ON		SetPin ( INFOTRONIC_GREEN , ON)
#define INFO_RED_ON			SetPin ( INFOTRONIC_RED , ON)

#define INFO_BLUE_OFF		SetPin ( INFOTRONIC_BLUE , OFF)
#define INFO_GREEN_OFF		SetPin ( INFOTRONIC_GREEN , OFF)
#define INFO_RED_OFF		SetPin ( INFOTRONIC_RED , OFF)



#define RELAY_ON		SetPin ( OUT0 , ON)
#define RELAY2_ON		SetPin ( OUT1 , ON)
#define RELAY3_ON		SetPin ( OUT2 , ON)

#define RELAY_OFF		SetPin ( OUT0 , OFF)
#define RELAY2_OFF		SetPin ( OUT1 , OFF)
#define RELAY3_OFF		SetPin ( OUT2 , OFF)

#define BUZZER_ON		SetPin ( OUT_BUZZER , OFF)	//BUZZER SE PRENDE CON OFF
#define BUZZER_OFF		SetPin ( OUT_BUZZER , ON)		//BUZZER SE APAGA CON ON
/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
extern volatile uint32_t BufferSalidas;		//!< Buffer de las salidas de los relays

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void RefrescoSalidas ( void );
void InicializarSalidas( void );

#endif /* DRIVERS_INFOTRONIC_INC_DR_SALIDAS_H_ */
