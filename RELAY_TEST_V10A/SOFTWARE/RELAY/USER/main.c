//说明:适用于RELAY_TEST_V10A板卡。
//功能:150s开电，10s关电
//by:xxxlzjxxx
//date:2019.04.25

#include "led.h"
#include "delay.h"
#include "sys.h"
#include "timer.h"

u16 count = 0;

int main(void)
 {	
	delay_init();	    	 //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	LED_Init();		  	//初始化与LED连接的硬件接口
	TIM3_Int_Init(10000,7199);//10Khz的计数频率，计数到10000为1000ms  
   	while(1)
	{
		LED0=!LED0;
		delay_ms(200);		   
	}
}
