#include "instruction_set.h"
#include "usart.h"
#include "SPI.h"

/***************  系统自检  ***************/
void Test(){
	uint32_t flash_id = Flash_ReadID();
	printf("\r\n====== System Selftest ======\r\n");
	
	if(flash_id != 0 && flash_id != 0xFFFFFF){ 							//Flash ID读取
        printf("\r\nFlash ID.......0x%06X (ok)\r\n", flash_id);
    } else {
        printf("\r\nFlash ID.......can not read\r\n");
    }
	
	if(SD_Is_Present() == 1){											//SD卡检测
		printf("\r\nTF card........ok\r\n");
	}else{
		printf("\r\nTF card........error\r\n");
	}
	
	printf("\r\n====== System Selftest ======\r\n");
}



/***************  时间设置  ***************/
/**********  设置基准时间  **********/
void RTC_Config(){
	
	
	
	
}

/**********  显示当前时间  **********/
void RTC_now(){
	
	
	
}


/***************  读取配置  ***************/
void cond(){
	
	
	
}
