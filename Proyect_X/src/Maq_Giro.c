/**
*	\file funciones.c
*	\brief
*	\details Descripcion detallada del archivo
*	\author CrisafienGerman
*	\date 15-09-2019 18:56:46
*/


#include "Maq_Giro.h"
#include "DR_IR.h"
#include "DR_tipos.h"
#include "Tanks.h"

//Implementacion Switch-Case

/**
*	\fn void maquina_estado()
*	\brief Implementacion Switch-Case
*	\details
*	\author CrisafienGerman
*	\date 15-09-2019 18:56:46
*/


//Declaracion de estados
#define 	IZQUIERDA				0
#define 	RESET					1
#define 	DERECHA					2
#define 	CUARENTAYCINCOGRADOS	3

#define		VELOCIDAD_GIRO	50


//
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

			default: estado = RESET;
		}

		return ENPROCESO;

}

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

