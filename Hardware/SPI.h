#ifndef __SPI_H
#define __SPI_H

#include "gd32f4xx_spi.h"
#include "stdint.h"

void SD_SPI_Init(void);
uint8_t SPI_ReadWriteByte(uint8_t byte);

#endif


