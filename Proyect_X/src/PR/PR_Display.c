#include "PR_Display.h"
#include "DR_tipos.h"
#include "DR_Display.h"









//-----------------------------------------------------------------

      //traduce de bcd al codigo del D7S (HACER)

uint8_t BUFFER_D7S[CANT_DIGITOS];     //

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


//systick
///HACER EL BARRIDO EN SERIO
void BarridoDisplay(void){
    //static char time = REFRESH_TIME -1; // sistick para 1 ms
    //if(!time){
        static uint8_t digito = 0;
        uint8_t auxiliar = BUFFER_D7S[digito];
        Apagar_D7S();
        SET_Digit(auxiliar, digito); //pinto no usar
        if(digito < CANT_DIGITOS)
            digito++;
        else
            digito = 0;
      //  time = REFRESH_TIME - 1;
    //}
    //else
    //    time --;
}




