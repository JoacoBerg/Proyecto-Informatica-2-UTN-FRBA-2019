/*******************************************************************************************************************************//**
 *
 * @file		Infotronic.h
 * @brief		Macros, tipos , prototipos, de la aplicacion
 * @date		23-03-16
 * @author		Tanks
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef DR_GPIOS_H_
#define DR_GPIOS_H_
/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#include "DR_tipos.h"

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/
typedef struct {
	__RW uint32_t	FIODIR;
	__R  uint32_t	RESERVED[3];//Espacio en blanco entre FIODIR y FIOMASK
	__RW uint32_t 	FIOMASK;
	__RW uint32_t 	FIOPIN;
	__RW uint32_t 	FIOSET;
	__RW uint32_t 	FIOCLR;
} gpio_t;

//0x2009C000UL : Direccion de inicio de los registros de GPIOs
#define		GPIOs		( (__RW gpio_t  * ) 0x2009C000UL )

//0x4002C040UL : Direccion de inicio de los registros de modo de los pines del GPIO
#define		PINMODE		( (__RW uint32_t  * ) 0x4002C040UL )

//open collector open drain
#define	 PINMODE_OD		( ( __RW uint32_t * )  0x4002C068UL )




//Estados de PinDir
#define PINDIR_OUTPUT	1
#define PINDIR_INPUT	0

//Estados de PinMode
#define		PINMODE_PULLUP 			0
#define		PINMODE_REPEAT			1
#define		PINMODE_HIGH_IMP 		2
#define		PINMODE_PULLDOWN 		3

#define 	PINMODE_OD_OFF			0
#define 	PINMODE_OD_ON			1


//Estados de PinMode_OD

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/


void SetPinDir(uint32_t Puerto, uint32_t Pin,uint32_t Dir);				//0: INPUT; 1: OUTPUT
void SetPinMode(uint32_t Puerto, uint32_t Pin,uint32_t Modo);		//pull up or pull down
void SetPinMode_OD(uint32_t Puerto, uint32_t Pin,uint32_t Modo);		//pull up or pull down
void SetPin (uint32_t Puerto, uint32_t Pin, uint32_t Estado);			//escritura del GPIO
uint32_t GetPin(uint8_t puerto , uint8_t bit , uint8_t actividad);						//lectura del GPIO

#endif /* DR_GPIOS_H_ */
