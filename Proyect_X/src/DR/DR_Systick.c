/*
 * DR_systick.c
 *
 *  Created on: 6 sep. 2019
 *      Author: gif30
 */
#include <DR_Salidas.h>
#include <DR_Systick.h>
#include "DR_Entradas.h"
#include "DR_Timers.h"
#include "PR_Display.h"
#include "PR_Teclado.h"


#include "DR_GPIO.h"

void SysTick_Init(void){
	Systick->STRELOAD = (Systick->STCALIB / 10) - 1; //Base de tiempo dada por 10ms/10: El -1 es porque cuenta uno de mas el STCURR
	Systick->STCURR = 0; //esto es para limpiar el timer

	Systick->ENABLE = 1; //activa el modulo
	Systick->TICKINT = 1; //activa la interrupcion
	Systick->CLKSOURCE = 1; //activa elige el clock del CPU en vez del clock externo por pin (STCLK)
}



void SysTick_Handler(void){
	BarridoDisplay();
	BarridoTeclado(check_teclas_Array);
	//cada 1 milisegundo

	//DebounceEntradas( );
	//RefrescoSalidas( );
	//AnalizarTimers( );


	/*
	static int i = 0;
	static int n = 0;
	i++;
	if(i==1000){
		Display7seg(n);
		n++;
		i=0;
	}
	*/

}
