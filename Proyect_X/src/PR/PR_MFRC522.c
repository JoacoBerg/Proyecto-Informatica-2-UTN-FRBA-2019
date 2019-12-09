/*
 * PR_SPI_MFRC522.c
 *
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
int Card(void)
{
	uint8_t status, checksum1, str[MAX_LEN];
	int isCard = 1;
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
	    if( 0x10 == checksum1 || 0x00 == checksum1)	//si no hay tarjeta
	    	isCard = 0;
	    //NOTA: el registro donde el MFRC522 guarda los ID se encuentra con contenido (distinto de 0 porque lo usa el modulo para inicializar)
	    // |-> cuando NO hay tarjeta se lee ese contenido y se guarda en buffer STR con SPI
	    // |-> cuando hay tarjeta el MFRC522 cola la ID en ese registro, despues se lee y se guarda en buffer STR con SPI

	    //CONCLUSION: si no hay tarjeta, se lee contenido que no es ID y se chequea con el CHECKSUM1

	    MFRC522_Halt(); //modo hibernacion
	  return isCard ;
}


//--------------------------- PRIMITIVAS: Read/Write ---------------------------------//
//mandan COMANDOS de 16 bits
//           |-> ESCRITURA: primeros 8 bits address y restantes valor a escribir
//			 |-> LECTURA: primeros 8 bits address a leer y restantes 0x00
//
//el SPI manda 8 bits y lee 8 bits simultaneamente (funcion MSS_SPI_transfer_frame)
// Casos:
//  |-> ESCRITURA: escribe la 'address' y lee 0x00, luego escribe 'valor' y lee 0x00
//	|-> LECTURA: escribe la 'address' y lee 0x00, luego escribe 0x00 y lee 8 bits que se encuentran en 'address'


//FUNCION Write_MFRC522: escribe 'val' en registro 'addr' (se manda un COMANDO DE ESCRITURA)
//
void Write_MFRC522(uint8_t addr, uint8_t val) {
  uint32_t rx_bits;

  SPI_ChipSelect_LOW();  //con GPIO -> empieza transferencia de bits con PIN Select(SSEL_PIN) en LOW

  rx_bits = MSS_SPI_transfer_frame( (((addr << 1) & 0x7E) << 8) |  val );
  rx_bits = rx_bits;
  SPI_ChipSelect_HIGH();  //con GPIO -> termina transferencia de bits con PIN Select(SSEL_PIN) en HIGH
}

//FUNCION Read_MFRC522: se lee de registro 'addr' (se manda un COMANDO DE LECTURA)
//Return: bits leidos
uint8_t Read_MFRC522(uint8_t addr) {
  uint32_t rx_bits;

  //con GPIO -> empieza transferencia de bits con PIN Select(SSEL_PIN) en LOW
  SPI_ChipSelect_LOW();

  rx_bits = MSS_SPI_transfer_frame(((((addr << 1) & 0x7E) | 0x80) << 8) | 0x00 );

  //con GPIO -> termina transferencia de bits con PIN Select(SSEL_PIN) en HIGH
  SPI_ChipSelect_HIGH();
	return (uint8_t) rx_bits; // return the rx bits (solo ultimos 8 bits de los 32)
}




