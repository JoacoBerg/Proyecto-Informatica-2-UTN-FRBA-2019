#include "DR_GPIO.h"
//Set sistickHandler 1MHz (1.000.000 Hz)


//ULTRASONICO 1
#define TRIG1 0,8
#define ECHO1 0,9

//ULTRASONICO 2
#define TRIG2 0,6
#define ECHO2 0,7

//ULTRASONICO 3
#define TRIG3 0,17
#define ECHO3 0,18


#define MAX_DIST 80
#define MAX_CONT 4000 //Distancia maxima que queremos que mida
#define CANT_FILTRO 10

typedef struct ULtrasonic_parameters {
	uint32_t cont1;
	uint32_t duracion;	
	uint32_t dato;
	uint32_t status;
	float dist;
	float prevdist;
	float DatoFiltrado;
	float dist_ant;
	uint32_t cant;

} ultra_s;


void InitUltraFR(uint32_t portTRIG,uint32_t pinTRIG, uint32_t portECHO,uint32_t pinECHO, ultra_s *u_gen);
uint32_t DistanciaUS(uint32_t portTRIG,uint32_t pinTRIG, uint32_t portECHO,uint32_t pinECHO, ultra_s *u_gen);
void FiltroUS(ultra_s *u_gen);
