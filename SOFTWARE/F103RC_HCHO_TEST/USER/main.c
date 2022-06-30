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
	u8 i=0, t=0;
    u16 k=5;
	u8 HCHObuf[15];
    u8 aa[20];
    u16 j=0;
    float hcho;    
	 
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	LCD_Init();			   	//��ʼ��LCD 			 	 
	HCHO_Init(9600);	//��ʼ����ȩ�������Ĵ���
	IIC_Init();
	SHT_Init();

 	POINT_COLOR=BLACK;//��������Ϊ��ɫ 			
    LCD_Fill(1,0,3,125,BLACK);
    LCD_Fill(0,119,320,121,BLACK);
 	POINT_COLOR=BLACK;//��������Ϊ��ɫ	  

    LCD_ShowString(20, 125, 8*26, 16, 16, "GB50325-2010: < 0.08 mg/m3");
    LCD_ShowString(20, 125+18, 12*19, 24, 24, "HCHO:         mg/m3");  
    LCD_ShowString(20, 125+18+26, 8*13, 16, 16,  "Temp:       C");
    LCD_ShowString(180, 125+18+26, 8*13, 16, 16, "Humi:       %");
	LCD_ShowString(4,125+18+26+20,200,16,16,"Sensor Data:");	//��ʾ���յ�������		
    
	while(1)
	{      
        HCHO_Receive_Data(HCHObuf,&key);
		if(1)//���յ�������
		{
			if(key>9){
                key=9;//�����9������.
            }
            POINT_COLOR=BLUE;//��������Ϊ��ɫ
 			for(i=0;i<key;i++){
                sprintf(aa,"0x%X",HCHObuf[i]);
                
                LCD_ShowString(4+i*35,125+18+26+20+20, 6*8, 16, 16, aa);
                LCD_ShowxNum(4+i*35,125+18+26+20+20+18,HCHObuf[i],3,12,0X80);	//��ʾ����
            }
            SHT_GetValue();//��ȡ��ʪ������    
            
            hcho = (HCHObuf[4] *256 + HCHObuf[5]) * 1.340625 / 1000;
            sprintf(aa,"%2.5f",hcho);//����������תΪָ����ʽ���ַ���        
            POINT_COLOR=BLUE;//��������Ϊ��ɫ
            LCD_ShowString(20+12*6, 125+18, 12*8, 24, 24, aa);
            
            sprintf(aa,"%2.2f",Tem_Value);//����������תΪָ����ʽ���ַ���
            POINT_COLOR=BROWN;
            LCD_ShowString(20+8*6, 125+18+26, 8*5, 16, 16, aa);
            
            sprintf(aa,"%2.2f",RH_Value);//����������תΪָ����ʽ���ַ���
            POINT_COLOR=BRRED;
            LCD_ShowString(180+8*6, 125+18+26, 8*5, 16, 16, aa);
    //�������ݻ���
            POINT_COLOR=BLUE;//��������Ϊ��ɫ       
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
            LED0=!LED0;//��ʾϵͳ��������
            LED1=!LED1;//��ʾϵͳ��������
        }
        
	} 
}





