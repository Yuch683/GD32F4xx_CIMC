#include "ADC.h"
#include "gd32f4xx_gpio.h"

void ADC0_Init(){
    rcu_periph_clock_enable(RCU_ADC0);    // 使能ADC0时钟
    rcu_periph_clock_enable(RCU_GPIOA);   // 使能GPIOA时钟（对应采集端口）
	adc_clock_config(ADC_ADCCK_PCLK2_DIV4); //4分频
	
	gpio_mode_set(ADC0_COLLECT_GPIO_PORT, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, ADC0_COLLECT_GPIO_PIN);
	
	adc_deinit();
	
	adc_sync_mode_config(ADC_SYNC_MODE_INDEPENDENT);	//独立模式

	adc_special_function_config(ADC0, ADC_SCAN_MODE, DISABLE);	//关闭扫描模式
    adc_special_function_config(ADC0, ADC_CONTINUOUS_MODE, DISABLE);	//关闭连续模式
    adc_data_alignment_config(ADC0, ADC_DATAALIGN_RIGHT);	// 数据右对齐
    adc_resolution_config(ADC0, ADC_RESOLUTION_12B);	// 12位分辨率
	
    adc_routine_channel_config(ADC0, 0, ADC0_COLLECT_CHANNEL, ADC_SAMPLETIME_144);
    adc_channel_length_config(ADC0, ADC_ROUTINE_CHANNEL, 1);
	adc_external_trigger_config(ADC0, ADC_ROUTINE_CHANNEL, EXTERNAL_TRIGGER_DISABLE);	//软件触发
	
    adc_enable(ADC0);
    
	delay_1ms(5); //延时5ms等待ADC稳定
    adc_calibration_enable(ADC0);
}

uint16_t ADC_Get_Value(void) {
    adc_software_trigger_enable(ADC0, ADC_ROUTINE_CHANNEL); 
    while( ! adc_flag_get(ADC0, ADC_FLAG_EOC));
    adc_flag_clear(ADC0, ADC_FLAG_EOC);
    return adc_routine_data_read(ADC0);
}
