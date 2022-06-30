#include "key.h"
#include "delay.h"


//������ʼ������
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOC,ENABLE);  //ʹ��GPIOA GPIOEʱ��
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;  //PE2,3,4����
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;  //����
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;  //��������

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;  //
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;  //����
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;  //��������
	GPIO_Init(GPIOC,&GPIO_InitStructure); 			//��ʼ��GPIOE
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;  //PA0����
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;  //��������
	GPIO_Init(GPIOA,&GPIO_InitStructure);     //��ʼ��GPIOA
}
/*******************************************************************************
* @param		KEY_Scan
* @brief		����������
* @arg			mode:0,��֧��������;1,֧��������;
* @return       0��û���κΰ�������
                1��KEY0_SW3_UP
                2��KEY1_SW5_CIRCLE
                3��KEY2_SW7_RETURN 
                4��KEY3_SW8_ENTER
                5��KEY4_SW6_START
                6��KEY5_SW4_DOWN
                7��WKUP_SW2_ONOFF
* @retval		u8
* @see			
* @attention	
* @note			ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>WK_UP!!	
* @author   	                                                                                                                               
* @date     	            				
*******************************************************************************/
#define KEY0_SW3_UP	    PEin(4)	//SW3
#define KEY1_SW5_CIRCLE	PEin(3) //SW5
#define KEY2_SW7_RETURN	PEin(2) //SW7
#define KEY3_SW8_ENTER	PCin(3)	//SW8
#define KEY4_SW6_START	PCin(2) //SW6
#define KEY5_SW4_DOWN	PCin(1)	//SW4
#define WKUP_SW2_ONOFF	PAin(0) //SW2

u8 KEY_Scan(u8 mode)
{
	static u8 key_up=1;   //�����ɿ���־
	if(mode){
        key_up=1;  //֧������
    }
    //�а�������
	if(key_up&&(KEY0_SW3_UP==0 || KEY1_SW5_CIRCLE==0 || KEY2_SW7_RETURN==0 || KEY3_SW8_ENTER==0 || KEY4_SW6_START==0 || KEY5_SW4_DOWN==0 || WKUP_SW2_ONOFF==1)){
		delay_ms(10);  //����ȥ��
		key_up=0;
		if(KEY0_SW3_UP==0) return 1;
		else if(KEY1_SW5_CIRCLE==0) return 2;
		else if(KEY2_SW7_RETURN==0) return 3;
		else if(KEY3_SW8_ENTER==0) return 4;
		else if(KEY4_SW6_START==0) return 5;
        else if(KEY5_SW4_DOWN==0) return 6;
		else if(WKUP_SW2_ONOFF==1) return 7;
	}else if(KEY0_SW3_UP==1 && KEY1_SW5_CIRCLE==1 && KEY2_SW7_RETURN==1 && KEY3_SW8_ENTER==1 && KEY4_SW6_START==1 && KEY5_SW4_DOWN==1 && WKUP_SW2_ONOFF==0){
        key_up=1; 
    }
	return 0; //�ް�������
}

