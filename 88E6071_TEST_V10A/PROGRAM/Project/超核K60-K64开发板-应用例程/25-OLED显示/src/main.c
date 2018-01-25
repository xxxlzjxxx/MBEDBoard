#include "gpio.h"
#include "common.h"
#include "uart.h"
//#include "i2c.h"
#include "cpuidy.h"

#include "myoled.h"


 
int main(void)
{
//    uint32_t  i;
	u8 t=0;
    DelayInit();
//    GPIO_QuickInit(HW_GPIOE, 6, kGPIO_Mode_OPP);
//	GPIO_QuickInit(HW_GPIOC, 8, kGPIO_Mode_OPP);
//	GPIO_QuickInit(HW_GPIOC, 9, kGPIO_Mode_OPP);
    UART_QuickInit(UART3_RX_PE05_TX_PE04, 115200);

    printf("Hello K60!\r\n");
    printf("CoreClock:%dHz\r\n", GetClock(kCoreClock));
    printf("BusClock:%dHz\r\n", GetClock(kBusClock));

	OLED_Init();				//初始化OLED
	OLED_ShowString(0,0,"HELLO WORLD...",12);    
	OLED_ShowString(0,52,"ASCII:",12);  
	OLED_ShowString(64,52,"CODE:",12);  
	OLED_Refresh_Gram();//更新显示到OLED
    t = ' ';
    while(1)
    {
		OLED_ShowChar(36,52,t,12,1);//显示ASCII字符	
		OLED_ShowNum(94,52,t,3,12);	//显示ASCII字符的码值    
		OLED_Refresh_Gram();        //更新显示到OLED
		t++;
		if(t>'~')t=' ';  
		DelayMs(500);
		printf(">>www.beyondcore.net \r\n");
    }
}


