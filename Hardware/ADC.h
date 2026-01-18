#ifndef __ADC_H
#define __ADC_H

#include <stdio.h>
#include <stdint.h>
#include "gd32f4xx_adc.h"
#include "systick.h"

// 定义默认采集通道（PA0）
#define ADC0_COLLECT_CHANNEL    ADC_CHANNEL_0
// 定义ADC采集端口（PA0）
#define ADC0_COLLECT_GPIO_PORT  GPIOA
#define ADC0_COLLECT_GPIO_PIN   GPIO_PIN_0

void ADC0_Init(void);
uint16_t ADC_Get_Value(void);

#endif /* __ADC_H */


