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
			if(IR_DER_IN == 1 && IR_IZQ_IN == 1)
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


/*

 MAQUINA DE ESTADOS DESCARTADA

#define 	IZQUIERDA				0
#define 	RESET					1
#define 	DERECHA					2
#define 	CUARENTAYCINCOGRADOS	3
uint8_t Maq_Giro(uint8_t orient)
{
		static uint8_t estado = RESET;

		switch(estado)
		{
			case IZQUIERDA:

				if(!IR_IZQ_IN && !IR_DER_IN)
				{

				 	estado = CUARENTAYCINCOGRADOS;

				}

				break;

			case DERECHA:

				if(!IR_IZQ_IN && !IR_DER_IN)
				{

					estado = CUARENTAYCINCOGRADOS;

				}

				break;

			case CUARENTAYCINCOGRADOS:

				if(IR_IZQ_IN && IR_DER_IN)
				{
					Frenar();
					estado = RESET;
					return EXITO;

				}

				break;
			case RESET:

				if(orient == IZQ)
				{
					FIzquierda();
					estado = IZQUIERDA;

				}
				if(orient == DER)
				{
					FDerecha();
					estado = DERECHA;

				}

				break;
			default: estado = RESET;
		}

		return ENPROCESO;

}
*/
//Funciones asociadas a los eventos

/**
*	\fn int esIzquierda(void)
*	\brief Resumen
*	\details Detalles
*	\author CrisafienGerman
*	\date 15-09-2019 18:56:46
*/


//Funciones asociadas a las acciones

/**
*	\fn void Frenar(void)
*	\brief Resumen
*	\details Detalles
*	\author CrisafienGerman
*	\date 15-09-2019 18:56:46
*/


