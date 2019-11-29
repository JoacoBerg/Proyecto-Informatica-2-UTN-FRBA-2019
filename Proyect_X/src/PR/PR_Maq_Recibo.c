/*
 * PR_Maq_Recibo.c
 *
 *  Created on: Nov 10, 2019
 *      Author: GCRIS
 */
#include "PR_Maq_Recibo.h"

int recepcionTrama(void){
	static uint8_t estado = 0;
	static int dato_posta = -1;
	int dato = UART1_PopRX();

	if(dato != -1){
		switch(estado){
			case 0:
				if('#' == dato)
					estado++;
				break;
			case 1:
				if('1'<=dato && dato<='4'){
					dato_posta = dato;
					estado++;
				}
				else
					estado=0;
				break;
			case 2:
				estado = 0;
				if('$' == dato)
					return dato_posta;
				break;
		}
	}
	return -1;
}

void Maq_Recibo(){

	int num = recepcionTrama();
	if(num != -1)
		Display7seg_BCD( num - '0' );

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


