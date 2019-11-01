
/*******************************************************************************************************************************//**
 *
 * @file		Inicializacion.c
 * @brief		Inicializaciones del Kit de Info II Infotronic
 * @date		23/03/16
 * @author		Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "DR_Salidas.h"
#include "DR_Entradas.h"
#include "DR_PLL.h"
#include "DR_SysTick.h"
#include "DR_Inicializacion.h"
#include "Tanks.h"
#include "Boton.h"



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
	//!< Se configura en primer lugar el PLL:
	//!< Estabiliza el oscilador interno del micro en 100MHz
	//!< Se configura el systic cada 1ms
	InicializarPLL();
	SysTick_Init();

	Tanks_Init();  //Servo init no existe, ya que el tanque se encarga de eso
	Boton_init();

	InicializarEntradas( ); //InitIR() no existe, las entradas se definen en InicializarEntradas()
	//InicializarSalidas( ); //NO Implementado
}
