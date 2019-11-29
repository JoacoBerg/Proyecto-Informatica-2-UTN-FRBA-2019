/*******************************************************************************************************************************//**
 *
 * @file		Template.c
 * @brief		Breve descripción del objetivo del Módulo
 * @date		Fecha de creacion del archivo XX/XX/XXXX
 * @author		Nombre, Apellido
 *
 */

#include "DR_Display.h"
#include "DR_PINSEL.h"
#include "DR_GPIO.h"


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

#define LETRA_R			0x50
#define LETRA_U			0x1C
#define LETRA_N			0x54
#define LETRA_T			0x78
#define LETRA_E			0x79
#define LETRA_P			0x73
#define LETRA_S			0x6D
#define LETRA_C			0x58
#define GUION			0x40
//#define PUNTO_D7S       0x12








//EXPANSION 2
//------------------------------------------------------------------

#define D7S_A  3,26
#define D7S_B  1,18
#define D7S_C  1,21
#define D7S_D  1,24
#define D7S_E  1,27
#define D7S_F  3,25
#define D7S_G  0,20
#define D7S_dp 1,19



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


uint8_t COMM_Pins_D7S[] = {    //las tierras del display
    2,7,
    1,29,
    4,28,
    1,23,
    1,20,
    0,19 //digito 1 segun kit
};

//-----------------------------------------------------------------




/*
//EXPANSION 3
//------------------------------------------------------------------


#define DBIN_0  2,7
#define DBIN_1  1,29
#define DBIN_2  4,28
#define DBIN_3  1,23

#define CANT_SEG_PINS			4
uint8_t SEG_Pins_D7S[] = {
	DBIN_0,
	DBIN_1,
	DBIN_2,
	DBIN_3,
};


#define CANT_DIGITOS			6      //cant digitos por display
uint8_t COMM_Pins_D7S[] = {    //las tierras del display
    2,7,
    1,29,
    4,28,
    1,23,
    1,20,
    0,19 //digito 1 segun kit
};

//-----------------------------------------------------------------
*/







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
	LETRA_R,	//Esta no es la mejor manera de hacerlo, pero me ahorra tiempo contando en el main
	LETRA_U,
	LETRA_N,
	LETRA_T,
	LETRA_E,
	LETRA_P,
	LETRA_P,
	LETRA_R,
	LETRA_E,
	LETRA_S,
	LETRA_T,
	LETRA_P,
	LETRA_E,
	LETRA_R,
	LETRA_R,
	GUION,
	LETRA_P,
	LETRA_C
	/*,
    PUNTO_D7S*/
};         //traduce de bcd al codigo del D7S

uint8_t BUFFER_D7S[CANT_DIGITOS];

//systick
void BarridoDisplay(void){
        static uint8_t digito = 0;
        uint8_t auxiliar = BUFFER_D7S[digito];
        Apagar_D7S();
        SET_Digit(auxiliar, digito); //pinto no usar
        if(digito < CANT_DIGITOS)
            digito++;
        else
            digito = 0;
}

//funciones internas del modulo
//prende un digito con numD7s siendo el codigo D7S
void SET_Digit(uint8_t numD7S, uint8_t dig){
    SetPin( COMM_Pins_D7S[(dig*2)],COMM_Pins_D7S[(dig*2)+1],HIGH);
    for(uint8_t segment= 0;segment < CANT_SEG_PINS; segment++)
    	SetPin( SEG_Pins_D7S[(segment*2)],SEG_Pins_D7S[(segment*2)+1],  (numD7S>>segment) & 1 );
}


void Apagar_D7S(void){
    SET_Digit(APAGAR_D7S, 0);
    for (uint8_t i = 0;i<CANT_DIGITOS;i++)
    	SetPin( COMM_Pins_D7S[(i*2)], COMM_Pins_D7S[(i*2)+1], LOW);
}

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
