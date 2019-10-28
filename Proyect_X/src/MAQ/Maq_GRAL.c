#include "Maq_GRAL.h"
#include "Maq_Giro.h"
#include "Maq_FollowTheLine.h"


//Declaracion de estados
#define 	SELECTION	0
#define 	BASE	    1
#define 	CAJA	    2
#define 	GIRO_IZQ	3
#define 	GIRO_DER	4
#define 	FORWARD	    5

void Maq_General()
{
		static uint8_t estado = BASE;

		switch(estado)
		{
			case SELECTION:
				estado = path_get();
				break;
			
			/*
			case BASE:
				if(Maq_Base())
					estado = SELECTION;
				break;
			
			case CAJA:
				if(Maq_Caja())
					estado = SELECTION;
				break;
			*/
			case GIRO_IZQ:
				if(Maq_Giro(IZQ))
					estado = SELECTION;
				break;
			
			case GIRO_DER:
				if(Maq_Giro(DER))
					estado = SELECTION;
				break;
			
			case FORWARD:
				if(Maq_FollowTheLine_v2())
					estado = SELECTION;
				break;
			
			default: estado = BASE;
		}


}
