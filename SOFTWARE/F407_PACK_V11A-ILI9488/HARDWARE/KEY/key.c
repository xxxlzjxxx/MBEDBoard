#include "key.h"
#include "delay.h"


//按键初始化函数
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOC,ENABLE);  //使能GPIOA GPIOE时钟
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;  //PE2,3,4引脚
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;  //输入
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;  //上拉输入

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;  //
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;  //输入
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;  //上拉输入
	GPIO_Init(GPIOC,&GPIO_InitStructure); 			//初始化GPIOE
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;  //PA0引脚
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;  //下拉输入
	GPIO_Init(GPIOA,&GPIO_InitStructure);     //初始化GPIOA
}
/*******************************************************************************
* @param		KEY_Scan
* @brief		按键处理函数
* @arg			mode:0,不支持连续按;1,支持连续按;
* @return       0，没有任何按键按下
                1，KEY0_SW3_UP
                2，KEY1_SW5_CIRCLE
                3，KEY2_SW7_RETURN 
                4，KEY3_SW8_ENTER
                5，KEY4_SW6_START
                6，KEY5_SW4_DOWN
                7，WKUP_SW2_ONOFF
* @retval		u8
* @see			
* @attention	
* @note			注意此函数有响应优先级,KEY0>KEY1>KEY2>WK_UP!!	
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
	static u8 key_up=1;   //按键松开标志
	if(mode){
        key_up=1;  //支持连按
    }
    //有按键按下
	if(key_up&&(KEY0_SW3_UP==0 || KEY1_SW5_CIRCLE==0 || KEY2_SW7_RETURN==0 || KEY3_SW8_ENTER==0 || KEY4_SW6_START==0 || KEY5_SW4_DOWN==0 || WKUP_SW2_ONOFF==1)){
		delay_ms(10);  //按键去抖
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
	return 0; //无按键按下
}

