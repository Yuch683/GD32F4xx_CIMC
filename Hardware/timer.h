#ifndef __TIMER_H
#define __TIMER_H

#include "systick.h"
#include "gd32f4xx_timer.h"
#include <stdio.h>

extern volatile uint32_t TIM1_COUNT;
extern volatile uint8_t adc_capture_flag;

void Timer1_Init(void);
void TIMER1_IRQHandler(void);

#endif /* __TIMER_H */


