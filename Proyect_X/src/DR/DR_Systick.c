#include <DR_Salidas.h>
#include <DR_Systick.h>
#include "DR_Entradas.h"
#include "DR_Timers.h"

void SysTick_Init(void){
	Systick->STRELOAD = (Systick->STCALIB / 4) - 1; //inicializo para 2,5ms
	Systick->STCURR = 0; //esto es para limpiar el timer

	Systick->ENABLE = 1; //activa el modulo
	Systick->TICKINT = 1; //activa la interrupcion
	Systick->CLKSOURCE = 1; //activa elige el clock del CPU en vez del clock externo por pin (STCLK)
}

void SysTick_Handler(void){

	//Funciones pedidas para el parcial
	BarridoDisplay(); //cada 2,5ms milisegundo
	DebounceEntradas( );
	AnalizarTimers( );
    RefrescoSalidas( );

}
