#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
//#include "usart.h"	 
#include "hcho.h"
 
/************************************************
 ALIENTEKս��STM32������ʵ��25
 485ͨ��ʵ�� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
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
	 
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
//	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	LCD_Init();			   	//��ʼ��LCD 	
//	KEY_Init();				//������ʼ��		 	 
	HCHO_Init(9600);	//��ʼ����ȩ�������Ĵ���
    
 	POINT_COLOR=BLACK;//��������Ϊ��ɫ 
//	LCD_ShowString(60,60,120,24,24,"HCHO TEST");			
    LCD_Fill(0,199,240,201,BLACK);
    LCD_Fill(4,0,6,210,BLACK);
 	POINT_COLOR=BLUE;//��������Ϊ��ɫ	  		
	LCD_ShowString(6,270,200,16,16,"Sensor Data:");	//��ʾ���յ�������		
    LCD_ShowString(6, 220, 8*25, 16, 16, "GB50325-2010: <0.08 mg/m3");

    
	while(1)
	{
		HCHO_Receive_Data(HCHObuf,&key);
		if(key)//���յ�������
		{
			if(key>15)key=15;//�����5������.
 			for(i=0;i<key;i++){
                LCD_ShowxNum(6+i*24,290,HCHObuf[i],3,12,0X80);	//��ʾ����
//                sprintf(bb[i],"%X",HCHObuf[i]);//����������תΪָ����ʽ���ַ���    
//                LCD_ShowString(10+i*24,280,24, 12, 12, &bb[i]);
                }
 		}
        
        hcho = (HCHObuf[4] *256 + HCHObuf[5]) * 1.340625 / 1000;
        sprintf(aa,"%2.5f",hcho);//����������תΪָ����ʽ���ַ���
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
            
			LED0=!LED0;//��ʾϵͳ��������	
			t=0;
		}		   
	} 
}





