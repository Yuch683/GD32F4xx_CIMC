#include "usart.h"

uint8_t rx_buffer[RX_BUFFER_SIZE];
volatile uint8_t rx_complete_flag = 0;
static uint8_t rx_index = 0;

void Usart2_Init(void)
{
	rcu_periph_clock_enable(RCU_USART_TX);
	rcu_periph_clock_enable(RCU_USART_RX);
	rcu_periph_clock_enable(RCU_USART2);
	
	gpio_af_set(GPIOC,GPIO_AF_7,GPIO_PIN_10 | GPIO_PIN_11);
	gpio_mode_set(GPIOC,GPIO_MODE_AF,GPIO_PUPD_PULLUP,GPIO_PIN_10 | GPIO_PIN_11);
	gpio_output_options_set(GPIOC,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_10);
	
	usart_deinit(USART2);
	
	usart_baudrate_set(USART2,9600);					//9600波特率
	usart_parity_config(USART2,USART_PM_NONE);			//无校验
	usart_word_length_set(USART2,USART_WL_8BIT);		//8位数据位
	usart_stop_bit_set(USART2,USART_STB_1BIT);			//1位停止位
	
	usart_enable(USART2);
	
	usart_transmit_config(USART2,USART_TRANSMIT_ENABLE);	//串口发送
	usart_receive_config(USART2,USART_RECEIVE_ENABLE);		//串口接收
	
	usart_interrupt_enable(USART2, USART_INT_RBNE);
}

void Usart2_NVIC(void){
	nvic_irq_enable(USART2_IRQn, 1, 0);
}

void USART2_IRQHandler(void)
{
	if(usart_interrupt_flag_get(USART2, USART_INT_FLAG_RBNE) != RESET){
		uint8_t data = (uint8_t)usart_data_receive(USART2);
		
		if(rx_complete_flag == 0){
			if(data == '\n'){
                rx_buffer[rx_index] = '\0'; // 添加字符串结束符，方便strcmp使用
                rx_complete_flag = 1;       // 标记接收完成
                rx_index = 0;                 // 索引归零，为下一次做准备
            }
            else if(data != '\r'){            // 忽略回车符 '\r'
                if(rx_index < RX_BUFFER_SIZE - 1){
                    rx_buffer[rx_index++] = data;
                }
			}
		}
	}
}

int fputc(int ch, FILE *f)					//printf函数重写
{
    usart_data_transmit(USART2, (uint8_t)ch);
    while(usart_flag_get(USART2, USART_FLAG_TC) == RESET);
    return (ch);
}
