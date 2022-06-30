#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
//#include "usart.h"	 
#include "hcho.h"
 
/************************************************
 ALIENTEK战舰STM32开发板实验25
 485通信实验 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

 				 	
 int main(void)
 {	 
	u8 key;
	u8 i=0,t=0;
    u16 k=10;
	u8 HCHObuf[15];
    u8 aa[100],bb[100];
    u16 j=0;
    float hcho;    
	 
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
//	uart_init(115200);	 	//串口初始化为115200
	LED_Init();		  		//初始化与LED连接的硬件接口
	LCD_Init();			   	//初始化LCD 	
//	KEY_Init();				//按键初始化		 	 
	HCHO_Init(9600);	//初始化甲醛传感器的串口
    
 	POINT_COLOR=BLACK;//设置字体为红色 
//	LCD_ShowString(60,60,120,24,24,"HCHO TEST");			
    LCD_Fill(0,199,240,201,BLACK);
    LCD_Fill(4,0,6,210,BLACK);
 	POINT_COLOR=BLUE;//设置字体为蓝色	  		
	LCD_ShowString(6,270,200,16,16,"Sensor Data:");	//提示接收到的数据		
    LCD_ShowString(6, 220, 8*25, 16, 16, "GB50325-2010: <0.08 mg/m3");

    
	while(1)
	{
		HCHO_Receive_Data(HCHObuf,&key);
		if(key)//接收到有数据
		{
			if(key>15)key=15;//最大是5个数据.
 			for(i=0;i<key;i++){
                LCD_ShowxNum(6+i*24,290,HCHObuf[i],3,12,0X80);	//显示数据
//                sprintf(bb[i],"%X",HCHObuf[i]);//浮点型数据转为指定格式的字符串    
//                LCD_ShowString(10+i*24,280,24, 12, 12, &bb[i]);
                }
 		}
        
        hcho = (HCHObuf[4] *256 + HCHObuf[5]) * 1.340625 / 1000;
        sprintf(aa,"%2.5f",hcho);//浮点型数据转为指定格式的字符串
        LCD_ShowString(6, 240, 12*5, 24, 24, "HCHO:");
        LCD_ShowString(6+12*5, 240, 12*8, 24, 24, aa);
        LCD_ShowString(6+12*5+12*8+12, 240, 12*5, 24, 24, "mg/m3");
        
        LCD_DrawPoint(k, 200*(1-hcho/0.16));

        
        t++; 
		delay_ms(10);
		if(t==100)
		{        
            k++;
            if(k==240){
            k=10;
            LCD_Fill(6,0,240,195, WHITE);
            }
            
			LED0=!LED0;//提示系统正在运行	
			t=0;
		}		   
	} 
}





