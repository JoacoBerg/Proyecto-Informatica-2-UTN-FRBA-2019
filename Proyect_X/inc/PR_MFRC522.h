/*
 * PR_SPI_MFRC522.h
 *
 *  Created on: Nov 2, 2019
 *      Author: GCRIS
 */

#ifndef PR_SPI_MFRC522_H_
#define PR_SPI_MFRC522_H_

#include <DR_MFRC522.h>
#include <PR_SPI.h>

void setup_MFRC522(void);
uint16_t Card(void);
uint16_t isCardRegistered (uint8_t checksum);
void Write_MFRC522(uint8_t addr, uint8_t val);
uint8_t Read_MFRC522(uint8_t addr);

//Elijo dispositivo con LOW (tener en cuenta que el spi puede tener varios chipSelect dependiendo la cantidad de dispositivos)
#define SPI_ChipSelect_LOW()	GPIO_Set( SSEL_PIN, LOW )
#define SPI_ChipSelect_HIGH()	GPIO_Set( SSEL_PIN, HIGH )


#endif /* PR_SPI_MFRC522_H_ */
