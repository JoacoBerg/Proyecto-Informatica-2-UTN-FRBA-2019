#include "PR_Display.h"
#include "DR_tipos.h"
#include "DR_Display.h"

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


//primitiva
void Display7seg_BCD(uint32_t val){ // val a cargar en el dsp asignado
    uint8_t i = 0;
    uint8_t aux[CANT_DIGITOS];
    for(i=0;i<CANT_DIGITOS;i++){
        aux[i]= Tabla_D7S[val%10];
        val=val/10;
    }
    /// opcional: deshabilitar la interrupcion
    for(i=0;i<CANT_DIGITOS;i++)
        BUFFER_D7S[i] = aux[i];
    /// opcional: rehabilitar la interrupcion
}

//
void Display7seg_per_digit_BCD(uint32_t val, uint8_t digit){ // val a cargar en el dsp asignado
        BUFFER_D7S[digit] = Tabla_D7S[val];
}





/*
void Display7seg_Binary(uint32_t val){ // val a cargar en el dsp asignado
    uint8_t i = 0;
    uint8_t aux[CANT_DIGITOS];
    for(i=0;i<CANT_DIGITOS;i++){
        aux[i]= val%10;
        val=val/10;
    }
    /// opcional: deshabilitar la interrupcion
    for(i=0;i<CANT_DIGITOS;i++)
        BUFFER_D7S[i] = aux[i];
    /// opcional: rehabilitar la interrupcion
}
*/





