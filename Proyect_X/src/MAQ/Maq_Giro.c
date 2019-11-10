#include "DR_tipos.h"
#include "Maq_Giro.h"
#include "DR_IR.h"
#include "Tanks.h"
#include "PR_Entradas.h"

//Implementacion Switch-Case

/**
*	\fn void maquina_estado()
*	\brief Implementacion Switch-Case
*	\details
*	\author CrisafienGerman
*	\date 15-09-2019 18:56:46
*/


//Declaracion de estados
#define CONTR    			0
#define RES     			1
#define EMPIEZA_A_GIRAR		2
#define DOBLANDO			3


#define		VELOCIDAD_GIRO	100


uint8_t Maq_Giro_v2(uint8_t orient)
{
	static uint8_t estado = RES;

	switch (estado)
	{

		case RES:
			if(IR_DER_IN == 1 || IR_IZQ_IN == 1) //PONEMOS UNA OR PARA QUE ARRANQUE SI CUALQUIERA DE LOS 2 ESTA EN LINEA NEGRA
			{
				switch(orient)
				{
					case DER:
						FDerecha();
						break;

					case IZQ:
						FIzquierda();
						break;

					default:
						estado = RES;
 						return FALLO;
						break;
				}
				estado = EMPIEZA_A_GIRAR;
			}
			break;

		case EMPIEZA_A_GIRAR:

			if(IR_DER_IN == 0 && IR_IZQ_IN == 0)
				estado = DOBLANDO;
			break;

		case DOBLANDO:
			if(IR_DER_IN == 1 && IR_IZQ_IN == 1){
				Frenar();
				estado = RES;
				return EXITO;
			}
			break;

		default:
			break;
	}

	return ENPROCESO;
}

void Frenar(void)
{
	Tank_Brake();
}

/**
*	\fn void FIzquierda(void)
*	\brief Resumen
*	\details Detalles
*	\author CrisafienGerman
*	\date 15-09-2019 18:56:46
*/
void FIzquierda(void){
	Tank_Left(VELOCIDAD_GIRO);
}

/**
*	\fn void FDerecha(void)
*	\brief Resumen
*	\details Detalles
*	\author CrisafienGerman
*	\date 15-09-2019 18:56:46
*/
void FDerecha(void){
	Tank_Right(VELOCIDAD_GIRO);
}
