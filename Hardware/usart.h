#ifndef __USART_H
#define __USART_H

#include "gd32f4xx_usart.h"
#include <stdio.h>
#include <string.h>

#define RCU_USART_TX 	RCU_GPIOC
#define RCU_USART_RX 	RCU_GPIOC
#define RX_BUFFER_SIZE	128		//定义缓冲区大小

extern uint8_t rx_buffer[RX_BUFFER_SIZE];
extern volatile uint8_t rx_complete_flag;

void Usart2_Init(void);
void Usart2_NVIC(void);
int fputc(int ch, FILE *f);
	
#endif /* __USART_H */


