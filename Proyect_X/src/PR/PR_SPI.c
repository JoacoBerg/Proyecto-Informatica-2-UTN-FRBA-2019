/*
 * PR_SPI.c
 *
 *  Created on: Nov 2, 2019
 *      Author: Tanks
 */


#include <PR_SPI.h>

void setup_SPI(void)
{
	/* Inicializo SPI 0 */
	SPI_init();
}

//FUNCION MSS_SPI_transfer_frame: utilizada para transferir 2 bytes consecutivos contenido en tx_bits
// argumento: tx_bits =
//					si es para WRITE -> tx_bits buffer de salida
//					si es para READ -> tx_bits debe ser un dummy (ej 0x00)

// CASO SPI_MFRC522: configuracion de MFRC522 por comandos
//
//					si es llamada para WRITE: tx_bits contiene address y dato a escribir en la direccion, recibe un dummy
//					si es llamada para READ: tx_bits contiene en los primeros 8 bits address, resto 0. Recibe dato que se encuentra en address

// return: dummy o dato leido
uint8_t MSS_SPI_transfer_frame(uint32_t tx_bits)
{
    volatile uint32_t dummy;

    /* Flush Rx FIFO. */
    while ( SPI->S0SPSR )
    {
        dummy = SPI->S0SPDR;
        dummy = dummy;  //para no warning de compilador por no usar variable
    }

    /* escribo 2 bytes. */
    SPI->S0SPDR = tx_bits;

    /* espero que se terminen de escribir -> SPIF = 1 */
    while ( SPI->S0SPSR == 0)
    {
        ;
    }

    /* En el mismo tiempo, que se transfiere un dato por el MOSI, llega otro por el MISO  */
    /* Return Rx data */
    return( SPI->S0SPDR );
}
