
#ifndef funciones_GPIO_h
#define funciones_GPIO_h

#include "DR_tipos.h"



//Estados de PINSEL:
#define		PINSEL_GPIO		0
#define		PINSEL_FUNC1	1
#define		PINSEL_FUNC2	2
#define		PINSEL_FUNC3	3




//Registros generales:
//0x4002C000UL : Direccion de inicio de los registros PINSEL
#define		PINSEL		( (__RW uint32_t  * ) 0x4002C000UL )
//0x400FC0C4UL : Direccion de inicio del registro de habilitación de dispositivos:
#define 	DIR_PCONP	( (__RW uint32_t  * ) 0x400FC0C4UL )

//0xE000E100UL : Direccion de inicio de los registros de habilitación (set) de interrupciones en el NVIC:
#define		ISER		( (__RW uint32_t  * ) 0xE000E100UL )
//0xE000E180UL : Direccion de inicio de los registros de deshabilitacion (clear) de interrupciones en el NVIC:
#define		ICER		( (__RW uint32_t  * ) 0xE000E180UL )


void SetPinsel(uint32_t Puerto, uint32_t Pin,uint32_t Configurar);

#endif
