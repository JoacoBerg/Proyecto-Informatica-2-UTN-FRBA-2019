/*
 * PR_SPI.h
 *
 *  Created on: Nov 2, 2019
 *      Author: Tanks
 */

#ifndef PR_SPI_H_
#define PR_SPI_H_

#include <DR_SPI.h>

void setup_SPI();
uint8_t MSS_SPI_transfer_frame(uint32_t tx_bits);



#endif /* PR_SPI_H_ */
