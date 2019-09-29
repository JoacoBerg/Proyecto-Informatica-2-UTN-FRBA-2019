#include "UltraLib.h"

void InitUltraFR(uint32_t portTRIG, uint32_t pinTRIG, uint32_t portECHO, uint32_t pinECHO, ultra_s *u_gen) {

	u_gen->cont1 = 0;
	u_gen->duracion = 0;
	u_gen->dato = 0;
	u_gen->status = 0;
	u_gen->dist = 0;
	u_gen->prevdist = 0;
	u_gen->DatoFiltrado = 0;
	u_gen->cant = 0;
	u_gen->dist_ant = 0;

	//ULTRASONICO 1
	GPIO_Set(portTRIG, pinTRIG, PINSEL_GPIO);
	GPIO_Mode(portTRIG, pinTRIG, PINMODE_PULLUP);
	GPIO_Dir(portTRIG, pinTRIG, OUTPUT);

	GPIO_Set(portECHO, pinECHO, PINSEL_GPIO);
	GPIO_Mode(portECHO, pinECHO, PINMODE_PULLUP);
	GPIO_Dir(portECHO, pinECHO, INPUT);
}

uint32_t DistanciaUS(uint32_t portTRIG, uint32_t pinTRIG, uint32_t portECHO, uint32_t pinECHO, ultra_s *u_gen) {
	//static ultra_s *u;
	//u = u_gen;

	u_gen->cont1++;
	switch (u_gen->cont1) {
	case 1:
		GPIO_Set(portTRIG, pinTRIG, OFF);
		break;
	case 6:
		GPIO_Set(portTRIG, pinTRIG, ON);
		break;
	case 16:
		GPIO_Set(portTRIG, pinTRIG, OFF);
		break;
	default:
		if (u_gen->cont1 > 16) {
			u_gen->dato = GPIO_Get(portECHO, pinECHO);
			if (1 == u_gen->dato && u_gen->status == 0) {
				u_gen->duracion = u_gen->cont1;
				u_gen->status = 1;
			}

			 if(u_gen->cont1 > MAX_CONT){
			 //u_gen->DatoFiltrado = MAX_DIST;
			 u_gen->cont1 = 0;
			 u_gen->duracion = 0;
			 u_gen->dato = 0;
			 //u_gen->status = 0;
			 //u_gen->dist = 0;
			 }
			 else
			 {
				if (0 == u_gen->dato && u_gen->status == 1) {
					u_gen->dist = u_gen->cont1 - u_gen->duracion;
					u_gen->dist /= 29;
					FiltroUS(u_gen);
					//printf("Pin: %d, cm = %0.2f\r\n", pinTRIG, u_gen->DatoFiltrado);
					u_gen->cont1 = 0;
					u_gen->status = 0;
					return 1;
				}
			 }
		}
		break;
	}

	return 0;
}

void FiltroUS(ultra_s *u_gen) {

	if (u_gen->dist > MAX_DIST || u_gen->cont1 > MAX_CONT)// el dato es erroneo (ruido), o no deseado
	{
		u_gen->DatoFiltrado = MAX_DIST;
		return;
	} else if (u_gen->cont1 < 29)
		return;
	else {

		if ( ((u_gen->dist > u_gen->dist_ant + 1) || (u_gen->dist < u_gen->dist_ant - 1)) && u_gen->cant < CANT_FILTRO ) {
			u_gen->dist = u_gen->dist_ant;
			u_gen->cant++;
		}

		else if (u_gen->cant == CANT_FILTRO) {
			u_gen->dist_ant = u_gen->dist;
			u_gen->cant = 0;
		}

		u_gen->DatoFiltrado = u_gen->dist;
	}

}
