/*******************************************************************************************************************************//**
 *
 * @file		DR_Display.c
 * @brief		Descripcion del modulo
 * @date		29 nov. 2019
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "DR_Display.h"
#include "DR_tipos.h"
#include "DR_PINSEL.h"
#include "DR_GPIO.h"

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/


/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/
uint8_t BUFFER_D7S[CANT_DIGITOS];

uint8_t COMM_Pins_D7S[] = {    //las tierras del display
    2,7,
    1,29,
    4,28,
    1,23,
    1,20,
    0,19 //digito 1 segun kit
};



uint8_t SEG_Pins_D7S[] = {
	D7S_A,
	D7S_B,
	D7S_C,
	D7S_D,
	D7S_E,
	D7S_F,
	D7S_G,
	D7S_dp
};

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/
/**
 *
 */

void Init_Display(void){

    for(uint8_t digit = 0; digit < CANT_DIGITOS ;digit ++){ // OUTPUTS
    	SetPinsel(COMM_Pins_D7S[(digit*2)], COMM_Pins_D7S[(digit*2)+1], PINSEL_GPIO);
        SetPinDir(COMM_Pins_D7S[(digit*2)], COMM_Pins_D7S[(digit*2)+1], PINDIR_OUTPUT);
        SetPinMode_OD(COMM_Pins_D7S[(digit*2)], COMM_Pins_D7S[(digit*2)+1], PINMODE_OD_OFF);
        SetPin(COMM_Pins_D7S[(digit*2)], COMM_Pins_D7S[(digit*2)+1], LOW);
    }

    for(uint8_t segment= 0;segment < CANT_SEG_PINS; segment++){
    	SetPinsel( SEG_Pins_D7S[(segment*2)],SEG_Pins_D7S[(segment*2)+1], PINSEL_GPIO);
        SetPinDir( SEG_Pins_D7S[(segment*2)],SEG_Pins_D7S[(segment*2)+1], PINDIR_OUTPUT);
        SetPinMode_OD( SEG_Pins_D7S[(segment*2)],SEG_Pins_D7S[(segment*2)+1], PINMODE_OD_OFF);
        SetPin( SEG_Pins_D7S[(segment*2)],SEG_Pins_D7S[(segment*2)+1], LOW);
    }
}



//funciones internas del modulo
//prende un digito con numD7s siendo el codigo D7S
void SET_Digit(uint8_t numD7S, uint8_t dig){
    SetPin( COMM_Pins_D7S[(dig*2)],COMM_Pins_D7S[(dig*2)+1],HIGH);
    for(uint8_t segment= 0;segment < CANT_SEG_PINS; segment++)
    	SetPin( SEG_Pins_D7S[(segment*2)],SEG_Pins_D7S[(segment*2)+1],  (numD7S>>segment) & 1 );
}


void Apagar_D7S(void){
    SET_Digit(0x00, 0);
    for (uint8_t i = 0;i<CANT_DIGITOS;i++)
    	SetPin( COMM_Pins_D7S[(i*2)], COMM_Pins_D7S[(i*2)+1], LOW);
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





