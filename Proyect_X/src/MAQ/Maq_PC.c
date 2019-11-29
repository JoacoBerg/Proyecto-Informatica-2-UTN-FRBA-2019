/*******************************************************************************************************************************//**
 *
 * @file		Template.c
 * @brief		Breve descripción del objetivo del Módulo
 * @date		Fecha de creacion del archivo XX/XX/XXXX
 * @author		Nombre, Apellido
 *
 */

#include <Maq_PCTransmision.h>
static uint8_t estadoMAQ_PC = RESET;
uint8_t START_TRANSMISION_FLAG = 0;
uint8_t ERROR_FLAG = 0; //si la PC no manda en 250 ms OK -> flag =1
uint8_t estadoRECV = 0;
void TimerHandler_ErrorPC_Reception()
{
	ERROR_FLAG = 1;
	estadoRECV = 0;
	estadoMAQ_PC = RESET;
	START_TRANSMISION_FLAG = 0;

	TimerStart(TIMER_ERROR, TIEMPO_ERROR , TimerHandler_Fin_De_Error, SEG);
}

void TimerHandler_Fin_De_Error()
{
	ERROR_FLAG = 0; //despues del tiempo de bloqueo
}

void Maq_PCTransmision(uint8_t NUM_CABINA, uint8_t ESTADO){
	 int dato;
	 volatile uint32_t estadoRECV = 0;

	 	 switch(estadoMAQ_PC)
	 	 {
				 case RESET:
					if(START_TRANSMISION_FLAG)
						estadoMAQ_PC = SENDUNG;

					 break;
				//----------------ESTADO ENVIO--------------------//
				 case SENDUNG:
					 UART1_PushTX('#');

					 UART1_PushTX(NUM_CABINA + '0');

					 switch(ESTADO)
					 {
					 case ESTADO_RUN:
						 UART1_PushTX('R');
						 UART1_PushTX('U');
						 UART1_PushTX('N');
						 break;

						 case ESTADO_TEP:
							 UART1_PushTX('T');
							 UART1_PushTX('E');
							 UART1_PushTX('P');
							 break;

						 case ESTADO_PRE:
							 UART1_PushTX('P');
							 UART1_PushTX('R');
							 UART1_PushTX('E');
							 break;

						 case ESTADO_STP:
							 UART1_PushTX('S');
							 UART1_PushTX('T');
							 UART1_PushTX('P');
							 break;

						 case ESTADO_ERR:
							 UART1_PushTX('E');
							 UART1_PushTX('R');
							 UART1_PushTX('R');
							 break;
					 }


						UART1_PushTX('$');
						estadoMAQ_PC ++;

						TimerStart(TIMER_PC, TIEMPO_PC , TimerHandler_ErrorPC_Reception, MIL250);

						START_TRANSMISION_FLAG = 0;
						break;


			//----------------ESTADO RECIBO--------------------//
			 case RECEPTION:

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
					 TimerStop(TIMER_PC);
					 estadoRECV = 0;
					 ERROR_FLAG = 0;
					 estadoMAQ_PC = 0;
				 }

			}
 }
