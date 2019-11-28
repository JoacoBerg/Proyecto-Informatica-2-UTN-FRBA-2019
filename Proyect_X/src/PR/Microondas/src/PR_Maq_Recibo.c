/*
 * PR_Maq_Recibo.c
 *
 *  Created on: Nov 10, 2019
 *      Author: GCRIS
 */
#include "PR_Maq_Recibo.h"

volatile int flag_Cooking=0;//no cocinando hasta que flag = 1
volatile int flagDesc = 0; //una sola vez llamo a TimerStart, despues se arregla

volatile int Level, tempo=0;
volatile uint8_t checksum = 0;
volatile uint8_t estadito = 0;

void handler_Descontar1(){
	tempo --;
	TimerStart(E_DESCONTAR2, T_DESCONTAR2, handler_Descontar2 , SEG );
}
void handler_Descontar2(){
	tempo --;
	TimerStart(E_DESCONTAR1, T_DESCONTAR1, handler_Descontar1 , SEG );
}


int recepcionTrama(void){
	uint16_t dato = UART1_PopRX();

	if(dato != -1){
		switch(estadito){
			case 0:
				if('>' == dato)
					estadito++;
				break;
			case 1:
				//----------NIVEL DE COCCION----------//
				if('0'<=dato && dato<='3'){
					Level = dato -'0';
					estadito++;
					checksum ^= dato;
				}
				else
					{
						estadito = 0;
						tempo = 0;
						checksum = 0;
					}
				break;

			case 2:
				//-----------TIEMPO[0]--------------//
				if('0'<=dato && dato<='9'){
					tempo += dato -'0';
					estadito++;
					checksum ^= dato;
				}
				else
				{
					estadito = 0;
					tempo = 0;
					checksum = 0;
				}
				break;

			case 3:
				//-----------TIEMPO[1]--------------//
				if('0'<=dato && dato<='9'){
					tempo += (dato -'0')*10;
					estadito++;
					checksum ^= dato;
				}
				else
				{
					estadito = 0;
					tempo = 0;
					checksum = 0;
				}
				break;

			case 4:
				//-----------TIEMPO[2]--------------//
				if('0'<=dato && dato<='9'){
					tempo += (dato -'0')*100;
					estadito++;
					checksum ^= dato;
				}
				else
				{
					estadito = 0;
					tempo = 0;
					checksum = 0;
				}
				break;

			case 5:
				//-----------TIEMPO[3]--------------//
				if('0'<=dato && dato<='9'){
					tempo += (dato -'0')*1000;
					estadito++;
					checksum ^= dato;
				}
				else
				{
					estadito = 0;
					tempo = 0;
					checksum = 0;
				}
				break;

			case 6:
				//-----------CHECKSUM--------------//
				if(checksum == dato || dato == (checksum - '0'))
						estadito ++;
				else
				{
					estadito = 0;
					tempo = 0;
					checksum = 0;
				}
				break;

			case 7:
				estadito = 0;
				if('<' == dato)
					return 1;
				else
				{
					estadito = 0;
					tempo = 0;
					checksum = 0;
				}
				break;
		}
	}
	return -1;
}

void Maq_Recibo(){

	static int num = 1;//queda ultimo valor de num

	if(!flag_Cooking)
	num = recepcionTrama();

	if(num != -1)
	{
		flag_Cooking =1; //empiezo a cocinar
		if(tempo >= 0)	//descuento
			{
				Display7seg_Binary(tempo);
				switch (Level)
				{
				case 1:
					RELAY_ON;
					break;

				case 2:
					RELAY_ON;
					RELAY2_ON;
					break;

				case 3:
					RELAY_ON;
					RELAY2_ON;
					RELAY3_ON;
					break;

				default:
					break;
				}
			}

		if(tempo == 0)
			{
				RELAY_OFF;
				flag_Cooking =0;
				flagDesc = 0;
				estado = RESET;
			}

		if(!flagDesc)	//llamo una vez a TimerStart, se queda descontando con timers que se llaman entre ellos
		{
			TimerStart(E_DESCONTAR1, T_DESCONTAR1, handler_Descontar1 , SEG );
			flagDesc = 1;
		}
	}


	/*
	int num = 0,aux = -1;

	num = UART1_PopRX();
	if( '#' == num )
	{
		do{
		num = UART1_PopRX();
		}while(num == -1);
		do{
		aux = UART1_PopRX();
		}while(aux == -1);
		if( '$' == aux)
			switch(num)
			{
				case 49:
					Display7seg_BCD( 1 );
					break;

				case 50:
					Display7seg_BCD( 2 );
					break;

				case 51:
					Display7seg_BCD( 3 );
					break;

				case 52:
					Display7seg_BCD( 4 );
					break;
			}

	}
*/
}


