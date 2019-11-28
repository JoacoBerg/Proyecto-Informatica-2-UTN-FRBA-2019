#include "PR_Teclado.h"
#include "DR_tipos.h"
#include "DR_GPIO.h"
#include "DR_PINSEL.h"


#define SW_1 2, 10
#define SW_2 0, 18


#define CANT_REBOTES_TECLADO 4

uint32_t CodigoActual = NO_KEY;  //entrada de teclado

uint8_t Tecla = NO_KEY; //tecla presionada debounced


#define CANT_COLUMNS_TECLADO 2
#define CANT_ROWS_TECLADO 4
#define CANT_ARRAY_TECLADO 2

//EXPANSION 3
uint8_t Teclado_COLUMNS[] = {    //OUTPUTS
    3, 25,
    1, 27
};

uint8_t Teclado_ROWS[] = {     //INPUTS
    1, 25,
	0, 20,
	1, 19,
    1, 22
};

//setear varios botones a la vez
uint8_t Teclado_Array[] = {
		SW_2,
		SW_1
};

void BarridoTeclado( uint8_t (*check_teclas) (void) ){
static uint8_t CodigoAnterior = NO_KEY;
static uint8_t Estados_estables = 0;
    CodigoActual = (*check_teclas)();

    if(CodigoActual == NO_KEY){
        CodigoAnterior = NO_KEY;
        Estados_estables = 0;
    }

    else if (Estados_estables == 0){
        CodigoAnterior = CodigoActual;
        Estados_estables = 1;
    }

    else if (Estados_estables == CANT_REBOTES_TECLADO){
        Estados_estables = CANT_REBOTES_TECLADO + 1;
        Tecla = CodigoAnterior;
    }

    else if(Estados_estables > CANT_REBOTES_TECLADO){}

    else if(CodigoAnterior == CodigoActual){
        Estados_estables ++;
    }
    else
        Estados_estables = 0;   //creo que esta linea es por si apretas muy rapido 2 botones distuint32_tos
}

uint8_t Lectura_Teclado (void){
    uint8_t Last_Tecla = Tecla;
    Tecla = NO_KEY;
    return Last_Tecla;
}

void Init_Teclado_Matrix(void){
    for(uint8_t column = 0; column< CANT_COLUMNS_TECLADO; column ++){ // OUTPUTS
    	SetPinsel(Teclado_COLUMNS[(column*2)], Teclado_COLUMNS[(column*2)+1], PINSEL_GPIO);
        SetPinDir(Teclado_COLUMNS[(column*2)], Teclado_COLUMNS[(column*2)+1], PINDIR_OUTPUT);
        SetPinMode_OD(Teclado_COLUMNS[(column*2)], Teclado_COLUMNS[(column*2)+1], PINMODE_OD_OFF);
        SetPin(Teclado_COLUMNS[(column*2)], Teclado_COLUMNS[(column*2)+1], HIGH);
    }

    for(uint8_t row = 0; row< CANT_ROWS_TECLADO; row ++){  //INPUTS
    	SetPinsel(Teclado_ROWS[(row*2)], Teclado_ROWS[(row*2)+1], PINSEL_GPIO);
    	SetPinDir(Teclado_ROWS[(row*2)], Teclado_ROWS[(row*2)+1], PINDIR_INPUT);
    	SetPinMode(Teclado_ROWS[(row*2)], Teclado_ROWS[(row*2)+1], PINMODE_PULLUP);
    }
}


void Init_Teclado_Array(void){
    for(uint8_t tecla = 0; tecla < CANT_ARRAY_TECLADO; tecla ++){  //INPUTS
    	SetPinsel(Teclado_Array[(tecla*2)], Teclado_Array[(tecla*2)+1], PINSEL_GPIO);
    	SetPinDir(Teclado_Array[(tecla*2)], Teclado_Array[(tecla*2)+1], PINDIR_INPUT);
    	SetPinMode(Teclado_Array[(tecla*2)], Teclado_Array[(tecla*2)+1], PINMODE_PULLUP);
    }
}

uint8_t check_teclas_Array(void){
	for(uint8_t tecla = 0; tecla < CANT_ARRAY_TECLADO; tecla++){
		if (LOW == GetPin(Teclado_Array[(tecla*2)], Teclado_Array[(tecla*2)+1]))
		return (tecla);
	}
	return NO_KEY;
}

uint8_t check_teclas_Matrix(void){
	for(uint8_t column = 0; column < CANT_COLUMNS_TECLADO ;column ++){
		ApagarTeclado();
		SetPin(Teclado_COLUMNS[(column*2)], Teclado_COLUMNS[(column*2)+1], LOW);
		for(uint8_t row = 0; row < CANT_ROWS_TECLADO; row++){
			if (LOW == GetPin(Teclado_ROWS[(row*2)], Teclado_ROWS[(row*2)+1]))
			return (row*CANT_COLUMNS_TECLADO+column);
		}
	}
	return NO_KEY;
}


void ApagarTeclado(void){
	for(uint8_t column = 0; column< CANT_COLUMNS_TECLADO ;column ++)
		SetPin(Teclado_COLUMNS[(column*2)], Teclado_COLUMNS[(column*2)+1], HIGH);
}
