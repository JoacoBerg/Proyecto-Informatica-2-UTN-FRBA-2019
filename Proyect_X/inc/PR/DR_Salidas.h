/*******************************************************************************************************************************//**
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

#define 	SD0	2, 0 //Pagina 4 del pfd infotronic adjunto en la entrega
#define		SD1	0, 16
#define		SD2	0, 27


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
