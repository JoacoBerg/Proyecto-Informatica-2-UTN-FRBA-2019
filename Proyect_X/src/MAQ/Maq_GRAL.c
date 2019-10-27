#include "Maq_GRAL.h"
#include "Maq_Giro.h"
#include "Maq_FollowTheLine.h"
#include "DR_tipos.h"


//Declaracion de estados
#define 	SELECTION	0
#define 	BASE	    1
#define 	CAJA	    2
#define 	GIRO_IZQ	3
#define 	GIRO_DER	4
#define 	FORWARD	    5



void Push_list_estados(uint8_t dato);
int32_t Pop_list_estados(void);


uint8_t Maq_Base(void){
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



#define TAM_BUFFER_list_estados 500
uint8_t lista_estados [TAM_BUFFER_list_estados];
uint8_t in_estados = 0;
uint8_t out_estados = 0;




void Push_list_estados(uint8_t dato){
	lista_estados[in_estados] = dato;
	in_estados++;
	if (in_estados>= TAM_BUFFER_list_estados)
		in_estados = 0;
}




int32_t Pop_list_estados(void){
	int32_t dato ;

	if(in_estados == out_estados) //the list is empty
		return -1;
	else{
		dato = lista_estados[out_estados];
		out_estados++;
		if (out_estados >= TAM_BUFFER_list_estados)
			out_estados = 0;
	}
	return dato;
}
