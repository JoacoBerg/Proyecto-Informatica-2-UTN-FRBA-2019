/*
 * PR_Teclado.h
 *
 *  Created on: 18 oct. 2019
 *      Author: gif30
 */

#ifndef PR_PR_TECLADO_H_
#define PR_PR_TECLADO_H_

#include "DR_tipos.h"
#define NO_KEY 84
void Init_Teclado(void);
uint8_t TecladoHW(void);
void TecladoSW(void);
uint8_t Lectura_Teclado (void);
void ApagarTeclado(void);
#endif /* PR_PR_TECLADO_H_ */
