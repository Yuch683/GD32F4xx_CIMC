#ifndef __GPIO_H
#define __GPIO_H

#include "SPI.h"

#define SD_CD_PIN       GPIO_PIN_2
#define SD_CD_PORT      GPIOE
#define SD_CD_CLK       RCU_GPIOE


void SD_Card_Init(void);
uint8_t SD_Is_Present(void);
uint32_t Flash_ReadID(void);

#endif /* __GPIO_H */


