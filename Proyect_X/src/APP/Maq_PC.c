#include "Maq_PC.h"


static uint8_t estadoMAQ_PC = RESET;
uint8_t flagSEND = 0;
uint8_t flagERROR = 0; //si la PC no manda en 250 ms OK -> flag =1
uint8_t estadoRECV = 0;
void handler_ERRORPC()
{
	flagERROR = 1;
	estadoRECV = 0;
	estadoMAQ_PC = RESET;
	flagSEND = 0;

	TimerStart(E_ERROR, T_ERROR , handler_BLOCK, SEG);
}

void handler_BLOCK()
{
	flagERROR = 0; //despues del tiempo de bloqueo
}

void Maquina_PC(uint8_t NUM_CABINA, uint8_t ESTADO){
	 int dato;
	 volatile uint32_t estadoRECV = 0;

	 	 switch(estadoMAQ_PC)
	 	 {
				 case RESET:
					if(flagSEND)
						estadoMAQ_PC = SEND;

					 break;

				//Estado envio
				 case SEND:
					 UART1_PushTX('#');

					 UART1_PushTX(NUM_CABINA + '0');

					 switch(ESTADO)
					 {
					 case RUN_e:
						 UART1_PushTX('R');
						 UART1_PushTX('U');
						 UART1_PushTX('N');
						 break;

						 case TEP:
							 UART1_PushTX('T');
							 UART1_PushTX('E');
							 UART1_PushTX('P');
							 break;

						 case PRE:
							 UART1_PushTX('P');
							 UART1_PushTX('R');
							 UART1_PushTX('E');
							 break;

						 case STP:
							 UART1_PushTX('S');
							 UART1_PushTX('T');
							 UART1_PushTX('P');
							 break;

						 case ERR:
							 UART1_PushTX('E');
							 UART1_PushTX('R');
							 UART1_PushTX('R');
							 break;
					 }


						UART1_PushTX('$');
						estadoMAQ_PC ++;

						TimerStart(E_PC, T_PC , handler_ERRORPC, MILISX250);

						flagSEND = 0;
						break;


			//estado recibir
			 case RECV:

				dato = UART1_PopRX();

				if(dato != -1){
					switch(estadoRECV){
						case 0:
							if('O' == dato)
								estadoRECV++;
							break;

						case 1:
							if('K' == dato)
								estadoRECV++;
							break;
					}
				}

				 if(estadoRECV == 2)
				 {
					 TimerStop(E_PC);
					 estadoRECV = 0;
					 flagERROR = 0;
					 estadoMAQ_PC = 0;
				 }

			}
 }
