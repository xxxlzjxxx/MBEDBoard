#ifndef _KEY_H
#define _KEY_H
#include "sys.h"
	

#define KEY0_SW3_UP	    PEin(4)	//SW3
#define KEY1_SW5_CIRCLE	PEin(3) //SW5
#define KEY2_SW7_RETURN	PEin(2) //SW7
#define KEY3_SW8_ENTER	PCin(3)	//SW8
#define KEY4_SW6_START	PCin(2) //SW6
#define KEY5_SW4_DOWN	PCin(1)	//SW4
#define WKUP_SW2_ONOFF	PAin(0) //SW2

#define KEY0_SW3_UP_PRES	    1
#define KEY1_SW5_CIRCLE_PRES    2
#define KEY2_SW7_RETURN_PRES	3
#define KEY3_SW8_ENTER_PRES	    4
#define KEY4_SW6_START_PRES	    5
#define KEY5_SW4_DOWN_PRES	    6
#define WKUP_SW2_ONOFF_PRES	    7

void KEY_Init(void);  //IO初始化
u8 KEY_Scan(u8);    //按键扫描函数
#endif 
