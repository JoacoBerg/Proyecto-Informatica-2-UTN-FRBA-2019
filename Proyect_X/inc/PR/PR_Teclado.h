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
void Init_Teclado_Matrix(void);
void Init_Teclado_Array(void);
uint8_t check_teclas_Matrix(void);
uint8_t check_teclas_Array(void);
void BarridoTeclado( uint8_t (*check_teclas) (void) );
uint8_t Lectura_Teclado (void);
void ApagarTeclado(void);
#endif /* PR_PR_TECLADO_H_ */
