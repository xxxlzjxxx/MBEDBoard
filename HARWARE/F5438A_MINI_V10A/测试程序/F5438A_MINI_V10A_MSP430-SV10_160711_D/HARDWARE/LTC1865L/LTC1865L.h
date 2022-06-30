/*****************************************************************************
** 文件名称：v.h （外部看门狗）
** 功    能：
** 修改日志：
******************************************************************************/
#ifndef __LTC1865L_H
#define __LTC1865L_H

/***************************************/

typedef unsigned char		uint8_t;  /*  8 bits */
typedef unsigned short int	uint16_t; /* 16 bits */
typedef unsigned long int	uint32_t; /* 32 bits */

/************************************************/

#define    SPIAD_Get_DI         SpiAD_GPIO_GetBit()

#define    SPIAD_SCLK_DIR_OUT        (P3DIR |= BIT7)      //设置时钟线为输出
#define    SPIAD_Set_SCLK       (P3OUT |= BIT7)           //拉高spiad时钟线
#define    SPIAD_Clr_SCLK       (P3OUT &= ~BIT7)          //拉低spiad时钟线

#define    SPIAD_DO_DIR_OUT        (P4DIR |= BIT1)        //设置时钟线为输出
#define    SPIAD_Set_DO         (P4OUT |= BIT1)           //ADC芯片数据输入线,输出1高电平
#define    SPIAD_Clr_DO         (P4OUT &= ~BIT1)          //ADC芯片数据输线,输出0低电平

#define    ADC_CH0    0x02
#define    ADC_CH1    0x03

#define    SPIAD_Conv_DIR_OUT        (P3DIR |= BIT6)      //LT1865L转换使能
#define    SPIAD_Set_Conv       (P3OUT |= BIT6)           //拉高控制位
#define    SPIAD_Clr_Conv       (P3OUT &= ~ BIT6)         //拉低控制位

#define    SPIAD_DI_DIR_IN           (P4DIR &=~BIT0)   //方向输入,ADC芯片数据输出引脚

void delay(uint16_t i);
uint16_t SpiAD_GPIO_GetBit(void);
void SpiAD_WriteTwoBit(uint8_t SDIBuffer);
uint16_t SpiAD_ReadTwoByte(void);
uint16_t LTC1865L_Read(uint8_t channel);


#endif
