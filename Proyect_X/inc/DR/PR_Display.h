/*
 * PR_Display.h
 *
 *  Created on: 18 oct. 2019
 *      Author: gif30
 */

#ifndef PR_PR_DISPLAY_H_
#define PR_PR_DISPLAY_H_
#include "DR_tipos.h"

void Display7seg_BCD(uint32_t val);
void Display7seg_Binary(uint32_t val);
void SET_Digit(uint8_t numD7S, uint8_t dig);
void BarridoDisplay(void);
void Apagar_D7S(void);
void Init_Display(void);

#endif /* PR_PR_DISPLAY_H_ */
