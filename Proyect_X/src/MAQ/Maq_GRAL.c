#include "Maq_GRAL.h"
#include "Maq_Giro.h"
#include "Maq_Base.h"
#include "Maq_FollowTheLine.h"
#include "DR_tipos.h"
#include "BUFFER_MAQ.h"


uint8_t Maq_Caja(void){
	static uint32_t i= 500000;

	if(i){
		i--;
		return 0;
	}
	else{
		i=500000;
		return 1;
	}
}



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
			
			case CAJA:
				if(Maq_Caja() == EXITO) //LECTURA DE RFID
					estado = SELECTION;
				break;
			case GIRO_IZQ:
				if(Maq_Giro(IZQ) == EXITO) //GIRO A 90° HACIA LA IZQUIERDA
					estado = SELECTION;
				break;
			
			case GIRO_DER:
				if(Maq_Giro(DER) == EXITO) //GIRO A 90° HACIA LA DERECHA
					estado = SELECTION;
				break;
			
			case FORWARD:
				if(Maq_FollowTheLine_v2() == EXITO) //AVANZAR
					estado = SELECTION;
				break;
			
			default: estado = SELECTION;
		}
}


