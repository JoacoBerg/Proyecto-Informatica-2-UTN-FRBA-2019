/*
 * PR_SPI_MFRC522.c
 *
 *  Created on: Nov 2, 2019
 *      Author: GCRIS
 */

#include <PR_MFRC522.h>

#define MAX_ID 4
//volatile uint8_t id[MAX_ID+1] = { 0xcb , 0x73 , 0xd7 , 0x73 , 0x00 };
volatile uint8_t id[MAX_ID+1] = { 0x95 , 0x32 , 0x78 , 0x89 , 0x00 };
//INICIALIZACION SPI Y MFRC522 (mediante comandos)
void setup_MFRC522() {
	/* Inicializo MFRC522 */
	MFRC522_Init();
}

//FUNCION Card: primitiva de MFRC522 para acceso por tarjeta magnetica
// return: hay tarjeta valida o no
uint16_t Card(void)
{
	uint8_t status, checksum1, str[MAX_LEN], isCard = 1;
	uint32_t i;
	    // Find cards
	    status = MFRC522_Request(PICC_REQIDL, str);

	    // Anti-collision, return: serial number == 4 bytes
	    status = MFRC522_Anticoll(str);
	    if (status == MI_OK)
	      checksum1 = str[0] ^ str[1] ^ str[2] ^ str[3];

	    for(i=0 ; i<MAX_ID ; i++)
	    {
	    	if( *(str+i) != *(id+i) )
	    		isCard = -1;
	    }
	    if( 0x10 == checksum1 || 0x00 == checksum1)
	    	isCard = 0;
	    MFRC522_Halt(); //modo hibernacion
	  return isCard ;
}

/*
 * Function Name：Write_MFRC5200
 * Function Description: To a certain MFRC522 register to write a byte of data
 * Input Parameters：addr - register address; val - the value to be written
 * Return value: None
 */
void Write_MFRC522(uint8_t addr, uint8_t val) {
  uint32_t rx_bits;

  // set the select line so we can start transferring
  SPI_ChipSelect_LOW();

  rx_bits = MSS_SPI_transfer_frame( (((addr << 1) & 0x7E) << 8) |  val );
  rx_bits = rx_bits;
  // clear the select line-- we are done here
  SPI_ChipSelect_HIGH();
}


/*
 * Function Name：Read_MFRC522
 * Description: From a certain MFRC522 read a byte of data register
 * Input Parameters: addr - register address
 * Returns: a byte of data read from the
 */
uint8_t Read_MFRC522(uint8_t addr) {
  uint32_t rx_bits;

  // set the select line so we can start transferring
  SPI_ChipSelect_LOW();

  // -Primeros 8 bits: address
  // -ultimos 8 bits: 0x00
  rx_bits = MSS_SPI_transfer_frame(((((addr << 1) & 0x7E) | 0x80) << 8) | 0x00 );

  // clear the select line-- we are done here
  SPI_ChipSelect_HIGH();
	return (uint8_t) rx_bits; // return the rx bits (solo ultimos 8 bits)
}




