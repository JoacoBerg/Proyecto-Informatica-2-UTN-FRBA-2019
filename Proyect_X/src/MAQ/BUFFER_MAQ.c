/*
 * BUFFER_MAQ.c
 *
 *  Created on: 27 oct. 2019
 *      Author: Tanks
 */

#include "BUFFER_MAQ.h"


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
