#include "led.h"
#include "delay.h"
//#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "hcho.h"
//#include "myiic.h"
#include "TemAndHum.h"
 
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
	u8 i=0, t=0;
    u16 k=5;
	u8 HCHObuf[15];
    u8 aa[20];
    u16 j=0;
    float hcho;    
	 
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
	LED_Init();		  		//初始化与LED连接的硬件接口
	LCD_Init();			   	//初始化LCD 			 	 
	HCHO_Init(9600);	//初始化甲醛传感器的串口
	IIC_Init();
	SHT_Init();

 	POINT_COLOR=BLACK;//设置字体为红色 			
    LCD_Fill(1,0,3,125,BLACK);
    LCD_Fill(0,119,320,121,BLACK);
 	POINT_COLOR=BLACK;//设置字体为蓝色	  

    LCD_ShowString(20, 125, 8*26, 16, 16, "GB50325-2010: < 0.08 mg/m3");
    LCD_ShowString(20, 125+18, 12*19, 24, 24, "HCHO:         mg/m3");  
    LCD_ShowString(20, 125+18+26, 8*13, 16, 16,  "Temp:       C");
    LCD_ShowString(180, 125+18+26, 8*13, 16, 16, "Humi:       %");
	LCD_ShowString(4,125+18+26+20,200,16,16,"Sensor Data:");	//提示接收到的数据		
    
	while(1)
	{      
        HCHO_Receive_Data(HCHObuf,&key);
		if(1)//接收到有数据
		{
			if(key>9){
                key=9;//最大是9个数据.
            }
            POINT_COLOR=BLUE;//设置字体为蓝色
 			for(i=0;i<key;i++){
                sprintf(aa,"0x%X",HCHObuf[i]);
                
                LCD_ShowString(4+i*35,125+18+26+20+20, 6*8, 16, 16, aa);
                LCD_ShowxNum(4+i*35,125+18+26+20+20+18,HCHObuf[i],3,12,0X80);	//显示数据
            }
            SHT_GetValue();//获取温湿度数据    
            
            hcho = (HCHObuf[4] *256 + HCHObuf[5]) * 1.340625 / 1000;
            sprintf(aa,"%2.5f",hcho);//浮点型数据转为指定格式的字符串        
            POINT_COLOR=BLUE;//设置字体为蓝色
            LCD_ShowString(20+12*6, 125+18, 12*8, 24, 24, aa);
            
            sprintf(aa,"%2.2f",Tem_Value);//浮点型数据转为指定格式的字符串
            POINT_COLOR=BROWN;
            LCD_ShowString(20+8*6, 125+18+26, 8*5, 16, 16, aa);
            
            sprintf(aa,"%2.2f",RH_Value);//浮点型数据转为指定格式的字符串
            POINT_COLOR=BRRED;
            LCD_ShowString(180+8*6, 125+18+26, 8*5, 16, 16, aa);
    //三种数据画线
            POINT_COLOR=BLUE;//设置字体为蓝色       
            LCD_DrawPoint(k, 110*((0.5-hcho)/0.5));
            
            POINT_COLOR=BROWN;
            LCD_DrawPoint(k, 110*((70-Tem_Value)/70));
            
            POINT_COLOR=BRRED;
            LCD_DrawPoint(k, 110*((99-RH_Value)/99));   
            
            k++; 
            if(k>=320){
                k=5;
                LCD_Fill(5,0,320,118, WHITE);
            }            
 		}       
        
        t++;
        delay_ms(10);
        if(t == 100){
            t = 0;           
            LED0=!LED0;//提示系统正在运行
            LED1=!LED1;//提示系统正在运行
        }
        
	} 
}





