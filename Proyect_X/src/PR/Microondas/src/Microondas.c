/*
 * Microondas.c
 *
 *  Created on: Nov 26, 2019
 *      Author: GCRIS
 */
#include "Microondas.h"
#include "DR_EXTINT.h"

//-----------VARIABLES GLOBAL---------------------
volatile uint8_t estado = RESET;
static uint32_t flag = 0, tiempo =0;
static uint8_t FlagLevel='0';
uint8_t flag_handler =0;

#define DIGITOS 	4

//TIEMPO int pasado a vector de chars
static uint8_t tempChars[DIGITOS];//4 digitos, incluye el 0 -> 0,1,2,3
//----------------------------------------------------
void IntToChar(uint32_t tiempo)
{
	uint32_t aux, i, num = tiempo;

	for( i=0 ; i<=DIGITOS ; i++)
	{
		aux = num % 10;
		*(tempChars + i) = aux + '0';
		num = num/10;
	}
}
void init_microondas()
{
	InicializarPLL();
	InicializarSysTick();
	UART1_Inicializacion(); // Inicializar en 9600-8N1

	init_extINT();
	//STICK 2
	Init_Display();
	//STICK 1
	Init_Teclado_Matrix();

	InicializarSalidas();
}

void handler_COOK()
{
	if(flag_handler ==0)
	{estado = COOK;} 	}

volatile static uint8_t checksum1=0;

void Microondas()//MAQ_ESTADOS
{
	uint32_t i;
	switch(estado)
	{
		case RESET:
			tiempo =0;
			FlagLevel = '0'; //nivel de coccion
			flag = 0;
			RELAY_OFF;

			UART1_PushTX('>');
			UART1_PushTX('0');
			UART1_PushTX('1');

			checksum1 = '0' ^ '1';		//suma de bytes

			UART1_PushTX(checksum1);
			UART1_PushTX('<');

			estado = GET_TIME;
			Display7seg_Binary(0);
			break;

		case GET_TIME:
			switch(Lectura_Teclado())
				{

			//--------NIVELES DE COCCION------------
					case NIVEL_MIN:
						if(FlagLevel == '0')
						FlagLevel = Min;
						break;

					case NIVEL_MED:
						if(FlagLevel == '0')
						FlagLevel = MED;
						break;

					case NIVEL_MAX:
						if(FlagLevel == '0')
						FlagLevel = MAX;
						break;

			//------------SUMA O RESTA DISPLAY--------
					case SUMA:
						flag = SLOW_SET;
						if(tiempo<9999)
							{tiempo++;}

							Display7seg_Binary(tiempo);
							break;

					case RESTA:
						if(tiempo>0)
							{tiempo--;}

							Display7seg_Binary(tiempo);
							break;


			//--------COMENZAR O CANCELAR--------
					case ENCENDIDO:
						if(flag != SLOW_SET)
						{
							FlagLevel = MAX;
							flag = QUICK_SET;
							tiempo +=10;
							Display7seg_Binary(tiempo);
							TimerStop(E_COOK);
							TimerStop(E_COOK);//por si acaso
							flag_handler = 0;
							TimerStart(E_COOK, T_WAIT, handler_COOK, SEG );
						}
						if(flag == SLOW_SET)
						{
							estado = COOK;
						}
						break;

				/*	case CANCEL:
						tiempo =0;
						FlagLevel = 0;
						TimerStop(E_COOK);
						Display7seg_Binary(tiempo);
						break;
*/
				}
				break;

			case COOK:

					UART1_PushTX('>');
					UART1_PushTX(FlagLevel); //NIVEL DE COCCION

					IntToChar(tiempo);
					for(i=0 ; i<DIGITOS ; i++)
						{
						//UART1_PushTX( (tiempo%10) + '0');
							UART1_PushTX( *(tempChars+i) );
							tiempo /=10;
						}

					//suma de bits
					checksum1 ^= FlagLevel;
					checksum1 ^= tempChars[3];
					checksum1 ^= tempChars[2];
					checksum1 ^= tempChars[1];
					checksum1 ^= tempChars[0];


					UART1_PushTX(checksum1);
					checksum1 = 0;

					UART1_PushTX('<');
					estado = COOKING;
					break;

			case COOKING:
				break;


	}//hacer funcion de lectura UART y que contemple el CANCEL
}

