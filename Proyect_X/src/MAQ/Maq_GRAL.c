#include "Maq_GRAL.h"
#include "Maq_Giro.h"
#include "Maq_Base.h"
#include "Maq_FollowTheLine.h"
#include "DR_tipos.h"
#include "BUFFER_MAQ.h"
#include "PR_Timers.h"

uint8_t Maq_Dummy(void);


void Maq_General()
{
		static int32_t estado = SELECTION;

		switch(estado)
		{
			case SELECTION:
				estado = Pop_list_estados();
				break;
			case BASE:
				if(Maq_Base() == EXITO) //LECTURA DE UART
					estado = SELECTION;
				break;
			
			case CAJA: //Maq_Caja()
				if(Maq_Dummy() == EXITO) //LECTURA DE RFID
					estado = SELECTION;
				break;
			case GIRO_IZQ:
				if(Maq_Giro_v2(IZQ) == EXITO) //GIRO A 90° HACIA LA IZQUIERDA
					estado = SELECTION;
				break;
			
			case GIRO_DER:
				if(Maq_Giro_v2(DER) == EXITO) //GIRO A 90° HACIA LA DERECHA
					estado = SELECTION;
				break;
			
			case FORWARD:
				ftl();
				if(Maq_FollowTheLine_v2() == EXITO) //AVANZAR
					estado = SELECTION;
				break;
			
			case FRENO:
				ftl();
				if(Maq_Freno() == EXITO) //AVANZAR
					estado = SELECTION;
				break;

			default: estado = SELECTION;
		}
}



#define RESET_DUMMY 0
#define WAIT_DUMMY 1
#define TIMER3 3

uint8_t waiting_dummy = OFF;

void TimerDummy(void){
	waiting_dummy = ON;
}


uint8_t Maq_Dummy(void){
	static uint8_t estado = RESET_DUMMY;
	switch(estado)
	{

		case RESET_DUMMY:

			TimerStart(TIMER3, 4, TimerDummy, SEG); //hago que vaya 1 decima de segundo para atras para que frene en el lugar
			waiting_dummy = OFF;
			estado = WAIT_DUMMY;
			break;

		case WAIT_DUMMY:

			if(waiting_dummy == ON){
				waiting_dummy = OFF;
				estado = RESET_DUMMY;
				return EXITO;
			}
			break;

		default:

			estado = RESET_DUMMY;
			break;

	}
	return ENPROCESO;
}



