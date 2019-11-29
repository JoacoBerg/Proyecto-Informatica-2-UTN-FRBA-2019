/*******************************************************************************************************************************//**
 *
 * @file		Template.c
 * @brief		Breve descripción del objetivo del Módulo
 * @date		Fecha de creacion del archivo XX/XX/XXXX
 * @author		Nombre, Apellido
 *
 ***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <DR_Inicializacion.h>
#include "DR_PLL.h"
#include "DR_SysTick.h"
#include "DR_Entradas.h"
#include "DR_Salidas.h"
#include "DR_Display.h"



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
 *** VARIABLES GLOBLES PRIVADAS AL MODULO
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
 \fn  void Inicializar ( void )
 \brief funcion principal
 \param void
 \return void
 */
void Inicializacion ( void )
{
	// Se configura en primer lugar el PLL:
	// Estabiliza el oscilador interno del micro en 100MHz
	InicializarPLL();
	SysTick_Init();
	// Se configura el systick cada 1ms

	UART1_Inicializacion();
	Init_Display();
	InicializarEntradas( );
	InicializarSalidas( );
}
