#include "gd32f4xx.h"
#include "timer.h"

volatile uint32_t TIM1_COUNT = 0;
volatile uint8_t adc_capture_flag = 0; 

void Timer1_Init(void){
	timer_parameter_struct timer_initpara;
	
	rcu_periph_clock_enable(RCU_TIMER1);
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
    timer_struct_para_init(&timer_initpara);
    timer_deinit(TIMER1);
	
	timer_initpara.prescaler = 239;
    timer_initpara.alignedmode = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection = TIMER_COUNTER_UP;
    timer_initpara.period = 9999;										//定时器频率：240Mhz / (240 * 10000) = 100hz  ->  0.1s
    timer_initpara.clockdivision = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
	
	timer_init(TIMER1, &timer_initpara);

	timer_auto_reload_shadow_enable(TIMER1);
    // 使能溢出中断
    timer_interrupt_enable(TIMER1, TIMER_INT_UP);
    // 配置中断优先级
    nvic_irq_enable(TIMER1_IRQn, 3, 0);
    // 启动定时器
    timer_enable(TIMER1);
}

void TIMER1_IRQHandler(void){
		if(timer_interrupt_flag_get(TIMER1,TIMER_INT_UP)){
		timer_interrupt_flag_clear(TIMER1,TIMER_INT_UP);
		
		TIM1_COUNT++;
		
		if(TIM1_COUNT % 100 == 0){										// LED每秒闪烁
			if(gpio_output_bit_get(GPIOA, GPIO_PIN_1) == SET){
				gpio_bit_reset(GPIOA, GPIO_PIN_1);
			}
			else{
				gpio_bit_set(GPIOA, GPIO_PIN_1);
			}
		}
	}
		if(TIM1_COUNT % 500 == 0){										// ADC每5秒采集
			adc_capture_flag = 1;
			
			if(TIM1_COUNT > 500)
				TIM1_COUNT = 0;
		}

}
