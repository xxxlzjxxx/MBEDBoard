#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "ili9488.h"
#include "led.h"
#include "sram.h"
#include "malloc.h"
#include "touch.h"
#include "GUI.h"
#include "timer.h"
#include "GUIDemo.h"
#include "key.h"
#include "touch.h" 
#include "string.h"	 	 
#include "gps.h"
#include "usmart.h"	
#include "usart3.h"
#include "bmp180.h"
#include "hmc5883l.h"

u8 USART1_TX_BUF[USART3_MAX_RECV_LEN]; 					//����1,���ͻ�����
nmea_msg gpsx; 											//GPS��Ϣ
__align(4) u8 dtbuf[50];   								//��ӡ������
const u8*fixmode_tbl[4]={"Fail","Fail"," 2D "," 3D "};	//fix mode�ַ��� 

extern BMP180_t BMP180;

//��ʾGPS��λ��Ϣ 
void Gps_Msg_Show(void)
{
 	float tp;		   
	POINT_COLOR=BLUE;  	 
	tp=gpsx.longitude;	   
	sprintf((char *)dtbuf,"Longitude:%.5f %1c   ",tp/=100000,gpsx.ewhemi);	//�õ������ַ���
 	LCD_ShowString(30,130,200,16,16,dtbuf);	 	   
	tp=gpsx.latitude;	   
	sprintf((char *)dtbuf,"Latitude:%.5f %1c   ",tp/=100000,gpsx.nshemi);	//�õ�γ���ַ���
 	LCD_ShowString(30,150,200,16,16,dtbuf);	 	 
	tp=gpsx.altitude;	   
 	sprintf((char *)dtbuf,"Altitude:%.1fm     ",tp/=10);	    			//�õ��߶��ַ���
 	LCD_ShowString(30,170,200,16,16,dtbuf);	 			   
	tp=gpsx.speed;	   
 	sprintf((char *)dtbuf,"Speed:%.3fkm/h     ",tp/=1000);		    		//�õ��ٶ��ַ���	 
 	LCD_ShowString(30,190,200,16,16,dtbuf);	 				    
	if(gpsx.fixmode<=3)														//��λ״̬
	{  
		sprintf((char *)dtbuf,"Fix Mode:%s",fixmode_tbl[gpsx.fixmode]);	
	  	LCD_ShowString(30,210,200,16,16,dtbuf);			   
	}	 	   
	sprintf((char *)dtbuf,"Valid satellite:%02d",gpsx.posslnum);	 		//���ڶ�λ��������
 	LCD_ShowString(30,230,200,16,16,dtbuf);	    
	sprintf((char *)dtbuf,"Visible satellite:%02d",gpsx.svnum%100);	 		//�ɼ�������
 	LCD_ShowString(30,250,200,16,16,dtbuf);		 
	sprintf((char *)dtbuf,"UTC Date:%04d/%02d/%02d   ",gpsx.utc.year,gpsx.utc.month,gpsx.utc.date);	//��ʾUTC����
	//printf("year2:%d\r\n",gpsx.utc.year);
	LCD_ShowString(30,270,200,16,16,dtbuf);		    
	sprintf((char *)dtbuf,"UTC Time:%02d:%02d:%02d   ",gpsx.utc.hour,gpsx.utc.min,gpsx.utc.sec);	//��ʾUTCʱ��
  	LCD_ShowString(30,290,200,16,16,dtbuf);		  
}	 

long hexToDec(char *source);
int getIndexOfSigns(char ch);


int main(void)
{ 
	u8 i,rxlen;
	u16 lenx;
    u8 temp[10];
    float x;
	u8 key=0XFF;
	u8 upload=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);      	//��ʼ����ʱ����
	uart_init(115200);			//��ʼ�����ڲ�����Ϊ115200 
	usart3_init(9600);			//��ʼ������3������Ϊ38400
	usmart_dev.init(84); 		//��ʼ��USMART		
	LED_Init();					//��ʼ��LED
	KEY_Init();					//��ʼ������
    BMP180_Init();				//��ʼ��BMP180
    bsp_InitHMC5883L();
    
 	ILI9488_Init();		 		//��ʼ��LCD
	usmart_dev.init(72); 		//��ʼ��USMART 	  
 	POINT_COLOR=RED;
	LCD_ShowString(30,20,200,16,16,"KEY TEST...");	

    BMP180_ReadCalibrationData();

	while(1){		
		delay_ms(1);
//		key=KEY_Scan(0);
//	   	if(key){	
//            LCD_Fill(30,100,240,120,WHITE);
//			switch(key){				 
//				case WKUP_SW2_ONOFF_PRES:
//					LCD_ShowString(30,100,200,16,16,"WKUP_SW2_ONOFF_PRES");
//					break;
//				case KEY0_SW3_UP_PRES:
//					LCD_ShowString(30,100,200,16,16,"KEY0_SW3_UP_PRES");
//					break;
//				case KEY1_SW5_CIRCLE_PRES: 
//					LCD_ShowString(30,100,200,16,16,"KEY1_SW5_CIRCLE_PRES");
//					break;
//				case KEY2_SW7_RETURN_PRES:
//					LCD_ShowString(30,100,200,16,16,"KEY2_SW7_RETURN_PRES");
//					break;
//				case KEY3_SW8_ENTER_PRES:
//					LCD_ShowString(30,100,200,16,16,"KEY3_SW8_ENTER_PRES");
//					break;
//				case KEY4_SW6_START_PRES:	 
//					LCD_ShowString(30,100,200,16,16,"KEY4_SW6_START_PRES");
//					break;
//				case KEY5_SW4_DOWN_PRES:
//					LCD_ShowString(30,100,200,16,16,"KEY5_SW4_DOWN_PRES");
//					break;
//                default:
//                    break;
//			}
//		}
		if((lenx%500)==0){
            LED0=!LED0;
//            if(BMP180_CheckID()){
//                
//                
//                i = BMP180.ID;  //16����:55h��10����:85
//                LCD_ShowNum(30,180,i,4,16);
//            

//                BMP_UncompemstatedToTrue();
//                sprintf(temp,"temp: %5.3f  C",(float)BMP180.Temp/10);
//                LCD_ShowString(30,200,200,16,16,temp);
//                sprintf(temp,"pres: %5.3f  Pa",(float)BMP180.p);
//                LCD_ShowString(30,220,200,16,16,temp); 
//                sprintf(temp,"altt: %5.3f  m",(float)BMP180.altitude);
//                LCD_ShowString(30,240,200,16,16,temp);
//            }else{
//                LCD_ShowString(30,200,200,16,16,"BMP180 ERROR!");
//            }
            
            HMC5883L_ReadData();
            LCD_ShowNum(30,260,g_tMag.X,5,16);
            LCD_ShowNum(30,280,g_tMag.Y,5,16);
            LCD_ShowNum(30,300,g_tMag.Z,5,16);
            
            LCD_ShowChar(30,200,g_tMag.IDReg[0],16,0);
            LCD_ShowChar(80,200,g_tMag.IDReg[1],16,0);
            LCD_ShowChar(140,200,g_tMag.IDReg[2],16,0);
        }            
		lenx++;	    
	}	
}



