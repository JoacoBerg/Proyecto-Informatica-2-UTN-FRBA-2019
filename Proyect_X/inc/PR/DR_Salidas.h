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

#ifndef DR_SALIDAS_H_
#define DR_SALIDAS_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "DR_tipos.h"



/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

#define 	SD0	0,28
#define		SD1	3, 26
#define		SD2	3, 25


#define SD0_ON		(BufferSalidas |= (1<<0))
#define SD1_ON		(BufferSalidas |= (1<<1))
#define SD2_ON		(BufferSalidas |= (1<<2))


#define SD0_OFF		(BufferSalidas &= ~(1<<0))
#define SD1_OFF		(BufferSalidas &= ~(1<<1))
#define SD2_OFF		(BufferSalidas &= ~(1<<2))

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
extern volatile uint32_t BufferSalidas;		//!< Buffer de las salidas de los relays

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void RefrescoSalidas ( void );
void InicializarSalidas( void );

#endif /* DR_SALIDAS_H_ */
