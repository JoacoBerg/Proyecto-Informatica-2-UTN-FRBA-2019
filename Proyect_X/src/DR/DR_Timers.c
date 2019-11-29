/*******************************************************************************************************************************//**
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "DR_Timers.h"
#include "DR_tipos.h"

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
volatile 	uint32_t Tmr_Run[ N_TIMERS ];
volatile 	uint8_t  TMR_Events[ N_TIMERS ];
void 	 	(* TMR_handlers [N_TIMERS]) (void);
volatile 	uint8_t  TMR_StandBy[ N_TIMERS ];
volatile 	uint8_t  Tmr_Base[ N_TIMERS ];

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

void AnalizarTimers(void)
{
	uint32_t i;
	for(i=0; i< N_TIMERS ; i++)
	{
		if(Tmr_Run[ i ])
		{
			if ( !TMR_StandBy[ i ] )
			{
				Tmr_Run[ i ]--;
				if(!Tmr_Run[ i ])
					TMR_Events[ i ] = 1;
			}
		}
	}
}

/**
	\fn void Timer_Event(void)
	\brief Chequeo de timers vencidos
 	\details Llama a los callbacks de los timers vencidos. Debe llamarse desde el lazo principal del programa
	\return void
*/
void TimerEvent(void)
{
	uint8_t i;
	for( i=0 ; i < N_TIMERS ; i++ )
	{
		if(TMR_Events[ i ])
		{
			TMR_handlers[ i ]( );
			TMR_Events[ i ] = 0;
		}
	}
}
