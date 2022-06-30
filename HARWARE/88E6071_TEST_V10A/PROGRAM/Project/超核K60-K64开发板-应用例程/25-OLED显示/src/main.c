#include "gpio.h"
#include "common.h"
#include "uart.h"
//#include "i2c.h"
#include "cpuidy.h"
#include "adc.h"
#include "myoled.h"


/* ���õ� ADCͨ�������� - 144P*/
/*
 ADC0_SE0_DP0        
 ADC0_SE1_DP1        
 ADC0_SE3_DP3        
 ADC0_SE4B_PC2       
 ADC0_SE5B_PD1       
 ADC0_SE6B_PD5       
 ADC0_SE7B_PD6       
 ADC0_SE8_PB0        
 ADC0_SE9_PB1        
 ADC0_SE12_PB2       
 ADC0_SE13_PB3       
 ADC0_SE14_PC0       
 ADC0_SE15_PC1       
 ADC0_SE17_E24       
 ADC0_SE18_E25       
 ADC0_SE19_DM0       
 ADC0_SE20_DM1       
 ADC0_SE26_TEMP      
 ADC1_SE0_DP0        
 ADC1_SE1_DP1        
 ADC1_SE3_DP3        
 ADC1_SE4_PE0        
 ADC1_SE5_PE1        
 ADC1_SE6_PE2        
 ADC1_SE7_PE3        
 ADC1_SE4B_PC8       
 ADC1_SE5B_PC9       
 ADC1_SE6B_PC10      
 ADC1_SE7B_PC11      
 ADC1_SE8_PB0        
 ADC1_SE9_PB1        
 ADC1_SE14_PB10      
 ADC1_SE15_PB11      
 ADC1_SE17_PB117     
 ADC1_SE19_DM0       
 ADC1_SE20_DM1       
 ADC1_SE26_TEMP      
*/	
int32_t Get_Adc0(u8 ch);
int32_t Get_Adc1(u8 ch);
int32_t Get_Adc0_Average(u8 ch,u8 times);
int32_t Get_Adc1_Average(u8 ch,u8 times);

int main(void)
{
	u16 adcx = 0;
	float temp=0;
	u16 t = 0;
//��ʼ��
    DelayInit();
//  GPIO_QuickInit(HW_GPIOE, 6, kGPIO_Mode_OPP);
//	GPIO_QuickInit(HW_GPIOC, 8, kGPIO_Mode_OPP);
//	GPIO_QuickInit(HW_GPIOC, 9, kGPIO_Mode_OPP);
    UART_QuickInit(UART3_RX_PE05_TX_PE04, 115200);
    /* ��ʼ��ADCģ�� ADC0_SE19_BM0 */
    ADC_InitTypeDef ADC_InitStruct1;
    ADC_InitStruct1.instance = HW_ADC0;
    ADC_InitStruct1.clockDiv = kADC_ClockDiv2; /* ADC����ʱ��2��Ƶ */
    ADC_InitStruct1.resolutionMode = kADC_SingleDIff16;
    ADC_InitStruct1.triggerMode = kADC_TriggerSoftware; /* �������ת�� */
    ADC_InitStruct1.singleOrDiffMode = kADC_Single; /*����ģʽ */
    ADC_InitStruct1.continueMode = kADC_ContinueConversionEnable; /* ��������ת�� ת��һ�κ� �Զ���ʼ��һ��ת��*/
    ADC_InitStruct1.hardwareAveMode = kADC_HardwareAverageDisable; /*��ֹ Ӳ��ƽ�� ���� */
    ADC_InitStruct1.vref = kADC_VoltageVREF;                       /* ʹ���ⲿVERFH VREFL ��Ϊģ���ѹ�ο� */
    
    ADC_InitStruct1.instance = HW_ADC1;
    ADC_InitStruct1.clockDiv = kADC_ClockDiv2; /* ADC����ʱ��2��Ƶ */
    ADC_InitStruct1.resolutionMode = kADC_SingleDIff16;
    ADC_InitStruct1.triggerMode = kADC_TriggerSoftware; /* �������ת�� */
    ADC_InitStruct1.singleOrDiffMode = kADC_Single; /*����ģʽ */
    ADC_InitStruct1.continueMode = kADC_ContinueConversionEnable; /* ��������ת�� ת��һ�κ� �Զ���ʼ��һ��ת��*/
    ADC_InitStruct1.hardwareAveMode = kADC_HardwareAverageDisable; /*��ֹ Ӳ��ƽ�� ���� */
    ADC_InitStruct1.vref = kADC_VoltageVREF;                       /* ʹ���ⲿVERFH VREFL ��Ϊģ���ѹ�ο� */	
	ADC_Init(&ADC_InitStruct1);
	
    printf("Hello K60!\r\n");
    printf("CoreClock:%dHz\r\n", GetClock(kCoreClock));
    printf("BusClock:%dHz\r\n", GetClock(kBusClock));

	OLED_Init();				//��ʼ��OLED
	OLED_ShowString(0,0,"...HELLO 88E6071...",12);    
	OLED_ShowString(0,14,"VOLT: 0.000V", 12);
	OLED_ShowString(0,28,"CURR: 0.000A", 12);
	OLED_ShowNum(36,42,t,4,12);
//	OLED_Refresh_Gram();//������ʾ��OLED
	OLED_ShowNum(0,42,t,4,12);
	/* ����һ��ADCת�� */
	ADC_StartConversion(HW_ADC0, 1, kADC_MuxA);
	ADC_StartConversion(HW_ADC1, 1, kADC_MuxA);

    while(1){
		if(ADC_IsConversionCompleted(HW_ADC0, kADC_MuxA) == 0){
		/* ��ȡADC��ֵ  kADC_MuxA��ÿ��ADCͨ����ת���� Ĭ�϶��� kADC_MuxA  MuxB һ�㲻������������� */
			adcx = ADC_ReadValue(HW_ADC0, kADC_MuxA);//�������һ��ADC1�������ת�����
	//		adcx=Get_Adc0_Average(1,10);
			temp=(float)adcx*(3.3/65535)/20/0.47;
			adcx=temp;
			OLED_ShowNum(36,14,adcx,1,12);	//��ʾ����ֵ
			temp-=adcx;
			temp*=1000;
			OLED_ShowNum(48,14,temp,3,12);
		}
		if(ADC_IsConversionCompleted(HW_ADC1, kADC_MuxA) == 0){
			adcx = ADC_ReadValue(HW_ADC1, kADC_MuxA);
			temp=(float)adcx*(3.3/65535)*1.5;
			adcx=temp;
			OLED_ShowNum(36,28,adcx,1,12);	//��ʾ��ѹֵ
			temp-=adcx;
			temp*=1000;
			OLED_ShowNum(48,28,temp,3,12);
		}
		t++;
		OLED_ShowNum(36,42,t,4,12);
		if(t == 9999){
			t = 0;
		}
		OLED_Refresh_Gram();        //������ʾ��OLED  
		DelayMs(500);		
    }
}

//���ADC0ֵ
//ch:ͨ��ֵ 0~3
int32_t Get_Adc0(u8 ch)   
{
	if(ADC_IsConversionCompleted(HW_ADC0, kADC_MuxA) == 0)
	{
		/* ��ȡADC��ֵ  kADC_MuxA��ÿ��ADCͨ����ת���� Ĭ�϶��� kADC_MuxA  MuxB һ�㲻������������� */
		return ADC_ReadValue(HW_ADC0, kADC_MuxA);//�������һ��ADC1�������ת�����
	}	
}
//���ADC1ֵ
//ch:ͨ��ֵ 0~3
int32_t Get_Adc1(u8 ch)   
{
	if(ADC_IsConversionCompleted(HW_ADC0, kADC_MuxA) == 0)
	{
		/* ��ȡADC��ֵ  kADC_MuxA��ÿ��ADCͨ����ת���� Ĭ�϶��� kADC_MuxA  MuxB һ�㲻������������� */
		return ADC_ReadValue(HW_ADC1, kADC_MuxA);//�������һ��ADC1�������ת�����
	}
}
//���ADC0ͨ��ch��ƽ��ֵ
int32_t Get_Adc0_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc0(ch);
		DelayMs(5);
	}
	return temp_val/times;
}
//���ADC1ͨ��ch��ƽ��ֵ
int32_t Get_Adc1_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc1(ch);
		DelayMs(5);
	}
	return temp_val/times;
}


