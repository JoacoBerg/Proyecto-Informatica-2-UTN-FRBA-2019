/*******************************************************************************************************************************//**
 *
 * @file		Template.c
 * @brief		Breve descripción del objetivo del Módulo
 * @date		Fecha de creacion del archivo XX/XX/XXXX
 * @author		Nombre, Apellido
 *
 */

#include <Maq_PCTransmision.h>
static uint8_t estado_PC = RESET;
uint8_t START_TRANSMISION_FLAG = 0;
uint8_t ERROR_FLAG = 0; //PC NO ENVIA OK -> FLAG =1
uint8_t estadoRECEPTION = 0;
void TimerHandler_ErrorPC_Reception()
{
	ERROR_FLAG = 1;
	estadoRECEPTION = 0;
	estado_PC = RESET;
	START_TRANSMISION_FLAG = 0;

	TimerStart(TIMER_ERROR, TIEMPO_ERROR , TimerHandler_Fin_De_Error, SEG);
}

void TimerHandler_Fin_De_Error()
{
	ERROR_FLAG = 0;
}

void Maq_PCTransmision(uint8_t cabin_nr, uint8_t cabin_status){
	 int dato;
	 volatile uint32_t estadoRECEPTION = 0;

	 	 switch(estado_PC)
	 	 {
				 case RESET:
					if(START_TRANSMISION_FLAG)
						estado_PC = SENDUNG;

					 break;

				 case SENDUNG:
					 UART1_PushTX('#');

					 UART1_PushTX(cabin_nr + '0');

					 switch(cabin_status)
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
						estado_PC ++;

						TimerStart(TIMER_PC, TIEMPO_PC , TimerHandler_ErrorPC_Reception, MIL250);

						START_TRANSMISION_FLAG = 0;
						break;



			 case RECEPTION:

				dato = UART1_PopRX();

				if(dato != -1){
					switch(estadoRECEPTION){
						case 0:
							if('O' == dato)
								estadoRECEPTION++;
							break;

						case 1:
							if('K' == dato)
								estadoRECEPTION++;
							break;
					}
				}

				 if(estadoRECEPTION == 2)
				 {
					 TimerStop(TIMER_PC);
					 estadoRECEPTION = 0;
					 ERROR_FLAG = 0;
					 estado_PC = 0;
				 }

			}
 }
