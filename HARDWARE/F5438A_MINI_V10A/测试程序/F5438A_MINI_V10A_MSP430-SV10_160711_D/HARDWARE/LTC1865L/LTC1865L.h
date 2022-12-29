/*****************************************************************************
** �ļ����ƣ�v.h ���ⲿ���Ź���
** ��    �ܣ�
** �޸���־��
******************************************************************************/
#ifndef __LTC1865L_H
#define __LTC1865L_H

/***************************************/

typedef unsigned char		uint8_t;  /*  8 bits */
typedef unsigned short int	uint16_t; /* 16 bits */
typedef unsigned long int	uint32_t; /* 32 bits */

/************************************************/

#define    SPIAD_Get_DI         SpiAD_GPIO_GetBit()

#define    SPIAD_SCLK_DIR_OUT        (P3DIR |= BIT7)      //����ʱ����Ϊ���
#define    SPIAD_Set_SCLK       (P3OUT |= BIT7)           //����spiadʱ����
#define    SPIAD_Clr_SCLK       (P3OUT &= ~BIT7)          //����spiadʱ����

#define    SPIAD_DO_DIR_OUT        (P4DIR |= BIT1)        //����ʱ����Ϊ���
#define    SPIAD_Set_DO         (P4OUT |= BIT1)           //ADCоƬ����������,���1�ߵ�ƽ
#define    SPIAD_Clr_DO         (P4OUT &= ~BIT1)          //ADCоƬ��������,���0�͵�ƽ

#define    ADC_CH0    0x02
#define    ADC_CH1    0x03

#define    SPIAD_Conv_DIR_OUT        (P3DIR |= BIT6)      //LT1865Lת��ʹ��
#define    SPIAD_Set_Conv       (P3OUT |= BIT6)           //���߿���λ
#define    SPIAD_Clr_Conv       (P3OUT &= ~ BIT6)         //���Ϳ���λ

#define    SPIAD_DI_DIR_IN           (P4DIR &=~BIT0)   //��������,ADCоƬ�����������

void delay(uint16_t i);
uint16_t SpiAD_GPIO_GetBit(void);
void SpiAD_WriteTwoBit(uint8_t SDIBuffer);
uint16_t SpiAD_ReadTwoByte(void);
uint16_t LTC1865L_Read(uint8_t channel);


#endif
