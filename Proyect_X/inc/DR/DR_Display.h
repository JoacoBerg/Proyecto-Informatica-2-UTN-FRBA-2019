/*******************************************************************************************************************************//**
 *
 * @file		Template.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		Fecha de creacion del archivo XX/XX/XXXX
 * @author		Nombre, Apellido
 *
 */

#ifndef DR_DR_DISPLAY_H_
#define DR_DR_DISPLAY_H_

#include "DR_tipos.h"


#define CANT_DIGITOS			6      //cant digitos por display (cuenta el 0), para el ejemplo son 3 digit

#define CANT_SEG_PINS			8

extern uint8_t Tabla_D7S[];
extern uint8_t BUFFER_D7S[];


void SET_Digit(uint8_t numD7S, uint8_t dig);
void BarridoDisplay(void);
void Apagar_D7S(void);
void Init_Display(void);

#endif /* DR_DR_DISPLAY_H_ */
