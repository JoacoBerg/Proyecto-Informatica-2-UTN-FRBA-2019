/*
 * BUFFER_MAQ.h
 *
 *  Created on: 27 oct. 2019
 *      Author: JoaquinBergmann
 */

#ifndef MAQ_BUFFER_MAQ_H_
#define MAQ_BUFFER_MAQ_H_

#include "DR_tipos.h"
//Declaracion de estados
#define 	SELECTION	's'
#define 	BASE	    'b'
#define 	CAJA	    'c'
#define 	GIRO_IZQ	'i'
#define 	GIRO_DER	'd'
#define 	FORWARD	    'f'

void Push_list_estados(uint8_t dato);
int32_t Pop_list_estados(void);


#endif /* MAQ_BUFFER_MAQ_H_ */
