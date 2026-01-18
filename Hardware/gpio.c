#include "gd32f4xx.h"
#include <stdio.h>
#include "gpio.h"
#include "systick.h"

/***************************************    —— SD卡 ——    ****************************************/

void SD_Card_Init(void)				//SD_card GPIO
{
    rcu_periph_clock_enable(SD_CD_CLK);
    gpio_mode_set(SD_CD_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, SD_CD_PIN);
}

uint8_t SD_Is_Present(void)			
{	
	delay_1ms(5); 
    /* 如果读取到低电平，说明卡插入接地了 */
    if(gpio_input_bit_get(SD_CD_PORT, SD_CD_PIN) == RESET) {

        return 1; // 卡存在
    } else {
        return 0; // 卡不存在
    }
}


/*************************************    —— 外部 FLASH ——    **************************************/
uint32_t Flash_ReadID(void) {
    uint32_t temp = 0;
    uint8_t id[3];

    // 1. 拉低片选
    gpio_bit_reset(GPIOB, GPIO_PIN_12);

    // 2. 发送读取 ID 指令 (0x9F)
    SPI_ReadWriteByte(0x9F);

    // 3. 连续读取 3 个字节
    id[0] = SPI_ReadWriteByte(0xFF); // 制造商 ID
    id[1] = SPI_ReadWriteByte(0xFF); // 设备 ID 高 8 位
    id[2] = SPI_ReadWriteByte(0xFF); // 设备 ID 低 8 位

    // 4. 拉高片选
    gpio_bit_set(GPIOB, GPIO_PIN_12);

    // 组合 ID
    temp = (id[0] << 16) | (id[1] << 8) | id[2];
    return temp;
}
