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
		static uint8_t estado = BASE;

		switch(estado)
		{
			case BASE:
				if(Maq_Base() == EXITO) //LECTURA DE UART
					estado = Pop_list_estados();
				break;
			
			case CAJA:
				if(Maq_Caja() == EXITO) //LECTURA DE RFID
					estado = Pop_list_estados();
				break;
			
			case GIRO_IZQ:
				if(Maq_Giro(IZQ) == EXITO) //GIRO A 90° HACIA LA IZQUIERDA
					estado = Pop_list_estados();
				break;
			
			case GIRO_DER:
				if(Maq_Giro(DER) == EXITO) //GIRO A 90° HACIA LA DERECHA
					estado = Pop_list_estados();
				break;
			
			case FORWARD:
				if(Maq_FollowTheLine() == EXITO) //AVANZAR
					estado = Pop_list_estados();
				break;
			
			default: estado = BASE;
		}
}


