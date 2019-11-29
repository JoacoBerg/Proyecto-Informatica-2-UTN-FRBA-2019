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





uint8_t Tabla_D7S[] = {
    CERO_D7S,
    UNO_D7S,
    DOS_D7S,
    TRES_D7S,
    CUATRO_D7S,
    CINCO_D7S,
    SEIS_D7S,
    SIETE_D7S,
    OCHO_D7S,
    NUEVE_D7S,
    APAGAR_D7S,
	R_MIN,
	U_MIN,
	N_MIN,
	T_MIN,
	E_MIN,
	P_MIN,
	P_MIN,
	R_MIN,
	E_MIN,
	S_MIN,
	T_MIN,
	P_MIN,
	E_MIN,
	R_MIN,
	R_MIN,
	GUION,
	P_MIN,
	C_MIN
	/*,
    PUNTO_D7S*/
};


#endif /* PR_PR_DISPLAY_H_ */
