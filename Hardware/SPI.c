#include "gd32f4xx.h"
#include "SPI.h"

void SD_SPI_Init(){
	spi_parameter_struct spi_init_struct;
	
	rcu_periph_clock_enable(RCU_SPI1);
	rcu_periph_clock_enable(RCU_GPIOB);
	
	gpio_af_set(GPIOB,GPIO_AF_5,GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
	gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
	gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
	
	gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_12);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_12);
	gpio_bit_set(GPIOB, GPIO_PIN_12); // 拉高 CS，停止片选
	
	spi_i2s_deinit(SPI1);
	
	spi_init_struct.trans_mode 					= SPI_TRANSMODE_FULLDUPLEX; 			// 全双工模式
	spi_init_struct.device_mode 				= SPI_MASTER; 							// 主机模式
	spi_init_struct.frame_size 					= SPI_FRAMESIZE_8BIT; 					// 数据帧大小为 8 位
	spi_init_struct.clock_polarity_phase 		= SPI_CK_PL_LOW_PH_1EDGE; 				// 时钟极性低，相位第一边沿
	spi_init_struct.nss 						= SPI_NSS_SOFT;							// 软件控制 NSS
	spi_init_struct.prescale 					= SPI_PSC_16; 							// 时钟分频
	spi_init_struct.endian 						= SPI_ENDIAN_MSB; 						// 高位优先
	
	spi_init(SPI1, &spi_init_struct);
	
	spi_enable(SPI1);
}

// 发送并接收一个字节
uint8_t SPI_ReadWriteByte(uint8_t byte) {
    while (RESET == spi_i2s_flag_get(SPI1, SPI_FLAG_TBE)); // 等待发送缓冲区空
    spi_i2s_data_transmit(SPI1, byte);
    while (RESET == spi_i2s_flag_get(SPI1, SPI_FLAG_RBNE)); // 等待接收缓冲区非空
    return spi_i2s_data_receive(SPI1);
}

