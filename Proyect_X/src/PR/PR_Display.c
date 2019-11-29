/*******************************************************************************************************************************//**
 *
 * @file		Template.c
 * @brief		Breve descripción del objetivo del Módulo
 * @date		Fecha de creacion del archivo XX/XX/XXXX
 * @author		Nombre, Apellido
 *
 */

#include "PR_Display.h"
#include "DR_tipos.h"
#include "DR_Display.h"





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
    /// opcional: rehabilitar la interrupcion
}


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



