#include "SistExt.h"
#include "DR_tipos.h"
#include "DR_Salidas.h"
#include "PR_Entradas.h"




void Set_SE(uint8_t cabina){
	switch(cabina){

	case 1:
		SD0_ON;
		SD1_OFF;
		SD2_OFF;
		break;
	case 2:
		SD0_OFF;
		SD1_ON;
		SD2_OFF;
		break;
	case 3:
		SD0_ON;
		SD1_ON;
		SD2_OFF;
		break;
	case 4:
		SD0_OFF;
		SD1_OFF;
		SD2_ON;
		break;
	case 5:
		SD0_ON;
		SD1_OFF;
		SD2_ON;
		break;
	case 6:
		SD0_OFF;
		SD1_ON;
		SD2_ON;
		break;
	}
}

uint8_t Get_SE(void){
	return (LEER_E2<<2) + (LEER_E1<<1) + (LEER_E0);
}
