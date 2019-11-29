#ifndef PR_PR_DISPLAY_H_
#define PR_PR_DISPLAY_H_
#include "DR_tipos.h"


void Display7seg_per_digit_BCD(uint32_t val, uint8_t digit);
void Display7seg_BCD(uint32_t val);
//void Display7seg_Binary(uint32_t val);


//codigo D7S
#define CERO_D7S        0x3F
#define UNO_D7S         0x06
#define DOS_D7S         0x5B
#define TRES_D7S        0x4F
#define CUATRO_D7S      0x66
#define CINCO_D7S       0x6D
#define SEIS_D7S        0x7D
#define SIETE_D7S       0x07
#define OCHO_D7S        0x7F
#define NUEVE_D7S       0x67
#define APAGAR_D7S      0x00

#define R_MIN			0x50
#define U_MIN			0x1C
#define N_MIN			0x54
#define T_MIN			0x78
#define E_MIN			0x79
#define P_MIN			0x73
#define S_MIN			0x6D
#define C_MIN			0x58
#define GUION			0x40
//#define PUNTO_D7S       0x12

#define CANT_DIGITOS			6
extern uint8_t BUFFER_D7S[CANT_DIGITOS];







#endif /* PR_PR_DISPLAY_H_ */
