/*******************************************************************************************************************************//**
 *
 * @file		Template.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		Fecha de creacion del archivo XX/XX/XXXX
 * @author		Nombre, Apellido
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef PRIMITIVAS_PR_TIMERS_H_
#define PRIMITIVAS_PR_TIMERS_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "DR_tipos.h"
#include "DR_Timers.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define     MIL250			0
#define 	DEC			1
#define 	SEG			2
#define 	MIN			3

#define 	RUN			0
#define 	PAUSE		1

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/

void TimerStart(uint8_t event, uint32_t time, Timer_Handler handler , uint8_t base );
void SetTimer( uint8_t event, uint32_t time );
uint32_t GetTimer( uint8_t event );
void StandByTimer( uint8_t event , uint8_t accion);
void TimerStop(uint8_t event);
void TimerClose(void);

#endif /* PRIMITIVAS_PR_TIMERS_H_ */
