/*
 * DR_SPI.h
 *
 *  Created on: Oct 5, 2019
 *      Author: GCRIS
 *
 *CONTENIDO DE SPI:
 *			-SCK: Serial Clock. Si micro Master -> empieza clock cuando BUFFER!=0
 *     		-SSEL: Slave Select
 *			-MISO: Master In Slave Out
 *			-MOSI: Master Out Slave In
 *			-LIMPIAR SPIF cada vez que se vaya a leer o escribir en BUFFER
 *			-Micro puede ser Master o Slave
 *			-Se puede expandir espacio de BUFFER de [8 a 16]bits (ver CONTROL REGISTER)
 *			-con CPOL=0 y CPHA=0 se toma dato cuando SCK HIGH
 *
 */

#ifndef DR_SPI_H_
#define DR_SPI_H_

#include "DR_tipos.h"
#include "DR_PLL.h"
#include "DR_GPIO.h"

//-------------------------------------------------------------------------------------------------------
#define SCK_CLCK 0b01	//0b00= CCLK/4		; 	0b01= CCLK	; 	0b10= CCLCK/2	;	 0b11= CCLCK/8
#define SPI_MODE 1//Modo que va a tomar el micro: 0: Slave ; 	1: Master
#define SPI_FUNCTION 3
//----------PINES----------------------------------------------------------------------------------------
#define SCK_PIN		0, 15 //alternativa en    0, 7  1, 20
#define SSEL_PIN	0, 16//alternativa en     0, 6   1, 21
#define MISO_PIN	 0, 17//alternativa en    0, 8  1, 23
#define MOSI_PIN	0, 18 //alternativa en	  0, 9   1, 24

//-------------FUNCIONES---------------------------------------------------------------------------------
void SPI_init(void);



typedef struct{//MAPA DE REGISTROS DE SPI

	union{
		__W uint32_t S0SPCR; //SPI CONTROL REGISTER (setea SPI0 con los siguientes parametros):
		struct{
			__RW uint32_t RESERVED_1:2;
			__RW uint32_t BitEnable:1;//0: send and receives 8 bits (DATALOW); 1: amplia BUFFER sumandole BITS(BITS=nombre de registro)
			__RW uint32_t CPHA:1;//0:muestra en primer flanco de SCK. Empieza cuando se activa SSEL signal; 1:
			__RW uint32_t CPOL:1;//Polarizacion de pulso SCK(tiempo). 0:SCK active high; 1:SCK active low
			__RW uint32_t MSTR:1;//Seleccion de Modo. 0: slave mode; 1:Master mode
			__RW uint32_t LSBF:1;//Sea BUFFER byte de transferencia. 0:MSB(lee BUFFER de izquierda a derecha); 1:LSB (derecha a izquierda)
			__RW uint32_t SPIE:1;//Habilitacion de INTERRUPCION. 0:interrupt inhibited; 1: interrupcion generada cada vez que SPIF o MODF se activen
			__RW uint32_t BITS:4;//si BitEnable=1 -> BITS=number of bits per transfer (Ej: 1000 = 8 bits per transfer. Ej2: 1100 = 12 bits per transfer. Ej3: 0000 = 16 bits per transfer)
			__RW uint32_t RESERVED_2:20;
		};
	};

	union{
		__RW uint32_t S0SPSR; //SPI STATUS REGISTER (los bits de este registro se BORRAN/LIMPIAN al ser leidos):
		struct{
			__RW uint32_t RESERVED_3:3;
			__RW uint32_t ABRT:1; //Se pone en 1 si el Slave se desconecta.
			__RW uint32_t MODF:1;//Se pone en 1 indicando falla de Modo(error set control).
			__RW uint32_t ROVR:1;//Se pone en 1 cuando read overrun (BUFFER lectura lleno)
			__RW uint32_t WCOL:1;//Se pone en 1 cuando write collision (BUFFER salida lleno)
			__RW uint32_t SPIF:1;//TRANSFER COMPLETE (flag) -> se pone 1. Ocurre en el ultimo ciclo de transferencia
			__RW uint32_t RESERVED_4:24;
		};
	};

	union{
		__RW uint32_t S0SPDR;//SPI BI-DIRECTIONAL DATA REGISTER(entradas y salidas):
//NOTAS DE DATA REGISTER: cuando se usa como MASTER, escribiendo en este registro se empieza el SPI data transfer.
//		cuando se empieza la transferencia se bloquea este buffer y no se puede escribir. Lo mismo ocurre con SPIF=1 (leyendo SPIF se limpia)
		struct{
			__RW uint32_t BUFFER:8;//puerto de SPI bi-directional
			__RW uint32_t DataHigh:8;//si BitEnable=1 -> se habilita este espacio para ampliar el BUFFER sumandole BITS(nombre de registro)
			__RW uint32_t RESERVED_5:16;
			};
		};

	union{
		__RW uint32_t S0SPCCR;//CONTROLS FREQUENCY OF MASTER's SCK0(frecuencia de pulsos de tiempo):
		struct{
			__RW uint32_t CLOCK:8;//setea SCK(numero de pulsos por ciclo). Si es Master-> T>=8. Si es Slave-> T< 1/8 de SPI of Master
			__RW uint32_t RESERVED_6:24;
			};
		};

/*	union{
		__RW uint32_t S0SPINT;//SPI INTERRUPT FLAG
		struct{
			__RW uint32_t SPINT:1;//se borra con un 1
		};
		__RW uint32_t RESERVED_7:31;
	};
*/
}spi_t;

#define SPI ((__RW spi_t *) 0x40020000UL)

#endif /* DR_SPI_H_ */
