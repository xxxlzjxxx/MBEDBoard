/*******************************************************************************
** ��Ȩ:     	xxxlzjxxx CO.,LTD
** �ļ���:   	main.c
** ��������: 	IAR 6.10
** ���̴�С:	
** ����:     	xxxlzjxxx
** ��������:	2016��7��11�� 
** ����:       F5438A_MINI_V10A_MSP430-SV10_160711_D
								  MSP430F5438A
-------------------------------------------------------------------------------
SP706R:     WDI ->P1.4
LED:        D3->P11.0
            D4->P11.1
            D5->P11.2
OLED:       CS  ->P8.0, RES->P8.2,  DC->P8.1,   D0(SCL)->P8.4,  D1(SDA)->P8.3
AT24Cxx:    SDA ->P3.0, SCL->P3.1
-------------------------------------------------------------------------------
** �������:
            MCU
** �޸���־��
			
*******************************************************************************/
/*******************************************************************************
									   _ooOoo_
									  o8888888o
									  88" . "88
									  (| -_- |)
									  O\  =  /O
								   ____/`---'\____
								 .'  \\|     |//  `.
								/  \\|||  :  |||//  \
							   /  _||||| -:- |||||-  \
							   |   | \\\  -  /// |   |
							   | \_|  ''\---/''  |   |
							   \  .-\__  `-`  ___/-. /
							 ___`. .'  /--.--\  `. . __
						  ."" '<  `.___\_<|>_/___.'  >'"".
						 | | :  `- \`.;`\ _ /`;.`/ - ` : | |
						 \  \ `-.   \_ __\ /__ _/   .-` /  /
					======`-.____`-.___\_____/___.-`____.-'======
									   `=---='
					^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
							 God Bless       Never Bug
*******************************************************************************/
/*********************************����ͷ�ļ�***********************************/

#include "includes.h"

/*********************************�Ӻ�������***********************************/
void ReadConfigInformation(void);
void Process(void);
float GetBatteryVoltage(void);
float GetTemperature(void);
void OLED_Display(void);
/***********************************�������***********************************/
float BatteryVoltage = 0, Temperature = 0;
unsigned int Flag_Timer1A0 = 0;
unsigned char cnt = 0;
/*******************************������*****************************************/
void main( void )
{  
    WDOG_Init(0);       //�ر��ڲ����Ź�
    GPIO_Init();
	SystemClock();      //ѡ���ⲿ20Mʱ��
	UsartInit();
    OLED_Init();
//********************��ȡEEPROM�����������Ϣ***********************************	
//	Ext_Wdog_Feed();
//	ReadConfigInformation();
//    Ext_Wdog_Feed();
//	
//	Usart_GPIO_Init();
//    Usart_Wire_Temp_Init_9600();
//	Send_232_data(y, 1);
//	Send_232_data(x, 2);
//	Send_232_data(y, 1);
	printf("\r\n_______________F5438A_MINI_V10A_MSP430-SV10_160711_D_______________\n\r");
	printf("\r\n                                  ���ߣ�xxxlzjxxx   \n\r");
	printf("\r\n>>ϵͳ��ʼ����ɣ�OLED��ʼ��ʾ��\n\r");
    Init_TimerA();
    OLED_Display();
    
	while(1)
    {
        _BIS_SR(LPM3_bits + GIE);		//����LPM3�ȴ�TA���ѣ����Ѻ��˳�
        
        if(Flag_Timer1A0 == 1)
        {
            Process();
        }
    }
}
/*******************************************************************************
** Name:			void ReadConfigInformation(void)
** Workspace: 		IAR 6.10 
** Designed by:	xxxlzjxxx
** Date: 			2015.10.13
** Function:		��ȡeeprom�е�������Ϣ
** Version:	
*******************************************************************************/
void ReadConfigInformation(void)
{
//  	P2OUT &= ~BIT5;		//Unable WriteProtect 	
//	EepromSequentialRead(0x00,	TerminalNum, 		6);	//default: {0x48,0x59,0x30,0x30,0x30,0x31}
//	EepromSequentialRead(0x01, 	SensorNum, 			4);
//	EepromSequentialRead(0x02, 	SamplingPeriod, 	2);	//default:	{0x00,0x00,0x00,0x0a} --> 10����
//	EepromSequentialRead(0x03, 	SamplingPoint, 		2);	//default:	{0x00,0x00,0x02,0x00} --> 512��
//	EepromSequentialRead(0x04, 	SamplingFrequency, 	2);	//default:	{0x00,0x00,0x02,0x00} --> 512Hz	
//	P2OUT |= BIT5;		//Enable WriteProtect
//	
//	Ext_Wdog_Feed();
////**************************�����ֽ�16����ת��Ϊ10����***************************	
//	FT = (SamplingPeriod[0] 	<< 8) | SamplingPeriod[1];
//	FP = (SamplingPoint[0] 		<< 8) | SamplingPoint[1];
//	FS = (SamplingFrequency[0] 	<< 8) | SamplingFrequency[1];	
}
/*******************************************************************************
** Name:			__interrupt void TIMER1_A0_ISR(void)
** Workspace: 		IAR 6.10 
** Designed by:	xxxlzjxxx
** Date: 			2015.07.31
** Function:		
** Version:	
*******************************************************************************/
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR(void)
{   
    LPM3_EXIT;
    Ext_Wdog_Feed();
    Flag_Timer1A0++;
    if(Flag_Timer1A0  == 2)
    {
        Flag_Timer1A0 = 0;
    }
}
/*******************************************************************************
** Name:			void Process(void)
** Workspace: 		IAR 6.10 
** Designed by:	xxxlzjxxx
** Date: 			2015.07.31
** Function:		���ϵͳ����
** Version:		
*******************************************************************************/
void Process(void)
{   
  	
    P11OUT ^= BIT0 + BIT1 + BIT2;
	printf("\n\r>>LED +%d\n\r", cnt);
	OLED_Display();
	cnt++;
	if(cnt == 255)
	{
		cnt = 0;
	}
}
/*******************************************************************************
** Name:			float GetBatteryVoltage(void)
** Return:        ���زɼ��ĵ�ѹֵ
** Function:		���ϵͳ����
                    100%----4.20V 
                ����90%-----4.06V 
                ����80%-----3.98V 
                ����70%-----3.92V 
                ����60%-----3.87V 
                ����50%-----3.82V 
                ����40%-----3.79V 
                ����30%-----3.77V 
                ����20%-----3.74V 
                ����10%-----3.68V 
                ����5%------3.45V 
                ����0%------3.00V
** Version:		
*******************************************************************************/
float GetBatteryVoltage(void)
{ 	
  	unsigned char i;
	float TempAvg = 0, Temp = 0;

  	for(i = 0; i < 5; i++)
	{
  		ADC12CTL0|=ADC12SC;
  		while(!(ADC12IFG & BIT0));
  		Temp = (float)ADC12MEM0 / 4096.0 * 3.17 * 2;  //*2Ϊ�����ѹ������f_dataΪʵ�ʵ�ѹֵ
		TempAvg = TempAvg + Temp;
		
		Ext_Wdog_Feed();
	}
	TempAvg = TempAvg / 5;

	return TempAvg;
} 
/******************************************************************************
** �������ƣ� float GetTemperature()
** ��    ��:  �ɼ�AD7414-0���¶ȣ�����5��(ɾ�����ֵ����Сֵ)�����ֵ
** �޸���־��
******************************************************************************/
float GetTemperature(void)
{
  	float TmpMax = -55, TmpMin = 125, TmpAvg = 0, Tmpre = 0;
	unsigned char i;
	
  	for(i = 0; i < 5; i++)
	{
  		Tmpre = AD7414_Read_Temp();
		TmpAvg = TmpAvg + Tmpre;
		if(Tmpre >= TmpMax)
		{
			TmpMax = Tmpre;
		}
		if(TmpMin >= Tmpre)
		{
			TmpMin = Tmpre;
		}
		
		Ext_Wdog_Feed();
	}
	TmpAvg = (TmpAvg - TmpMax - TmpMin) / 3;
  	Ext_Wdog_Feed();
	
	return TmpAvg;
}
void OLED_Display(void)
{
//    OLED_Clear();
//  ͼƬ��ʾ(ͼƬ��ʾ���ã����ɵ��ֱ�ϴ󣬻�ռ�ý϶�ռ䣬FLASH�ռ�8K��������)    
//	OLED_DrawBMP(37, 0, 128, 8, bmp1);     
//    OLED_ShowCHinese(19,5,0);
//    OLED_ShowCHinese(37,5,1);
//    OLED_ShowCHinese(55,5,2);
//    OLED_ShowCHinese(73,5,3);
//    OLED_ShowCHinese(91,5,4);
//    delay_ms(1000);
//    OLED_Clear();       
    
    OLED_ShowString(37,0,"xxxlzjxxx");  
    OLED_ShowString(34,2,"2016/07/11");  
    OLED_ShowString(8,6,"LED +");  
	OLED_ShowNum(64,6,cnt,3,16);
    //OLED_ShowString(63,6,"CODE:");  
    //OLED_ShowChar(48,6,t);//��ʾASCII�ַ�	   
    //t++;
    //if(t>'~')t=' ';
    //OLED_ShowNum(64,6,t,3,16);//��ʾASCII�ַ�����ֵ 	
//					
//		delay_ms(250);
//		OLED_Clear();
//		//delay_ms(250);
//		delay_ms(500);
//		OLED_DrawBMP(0,0,128,8,BMP2);
//		delay_ms(1000);
}
