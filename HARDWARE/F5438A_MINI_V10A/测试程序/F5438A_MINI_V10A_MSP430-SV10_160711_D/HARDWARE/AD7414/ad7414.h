/*******************************************************************************
* File Name  ��ad7414.h
* Function   ��Function declaration
* Author     ��
* Version    ��
* Description��
* Chang Log  ��
*******************************************************************************/
#ifndef __AD7414_H
#define __AD7414_H

/*****************************************************************************
* �ܽŶ���
*****************************************************************************/
#define   SDA_AD7414_SEL_GPIO                  (P1SEL &=~BIT1)  //����ΪGPIO��
#define   SDA_AD7414_DIR_OUTPUT                (P1DIR |= BIT1)  //�������
#define   SDA_AD7414_DIR_INPUT                 (P1DIR &=~BIT1)  //��������
#define   SDA_AD7414_OUT_HIGH                  (P1OUT |= BIT1)  //�����
#define   SDA_AD7414_OUT_LOW                   (P1OUT &=~BIT1)  //�����

#define   SDA_AD7414_DIR_INPUT                 (P1DIR &=~BIT1)  //����
#define   SDA_AD7414_READ                      (P1IN&BIT1)      //���ܽŵ�ƽ״̬

#define   SCL_AD7414_SEL_GPIO                  (P1SEL &=~BIT0)  //����ΪGPIO��
#define   SCL_AD7414_DIR_OUTPUT                (P1DIR |= BIT0)  //�������
#define   SCL_AD7414_DIR_INPUT                 (P1DIR &=~BIT0)  //��������
#define   SCL_AD7414_OUT_HIGH                  (P1OUT |= BIT0)  //�����
#define   SCL_AD7414_OUT_LOW                   (P1OUT &=~BIT0)  //�����

#define   AD7414_ALT_SEL_GPIO                  (P1SEL &=~BIT2)  //����ΪGPIO��
#define   AD7414_ALT_DIR_INPUT                 (P1DIR &=~BIT2)  //��������


#define AD7414IICAddress	0x48	//	1001 000
//#if 1
#define AD7414_WriteDeviceAddress       0x90          //AD7414-0's Write Address 1001 000 0
#define AD7414_ReadDeviceAddress        0x91          //AD7414-0's Read  Address 1001 000 1
//#endif

//#if 0
//#define AD7414_WriteDeviceAddress       0x9A          /*AD7414-1's Write Address*/
//#define AD7414_ReadDeviceAddress        0x9B          /*AD7414-1's Read  Address*/
//#endif

/*******************************************************************************
* ��������
*******************************************************************************/
void AD7414_Init(void);
void AD7414_I2c_Start(void);
void AD7414_I2c_Stop(void);
void AD7414_I2cAck_Slaver(void);
void AD7414_I2cNoAck_Mcu(void);
void AD7414_I2cWriteByte(unsigned char wbyte);
unsigned char AD7414_I2cReadByte(void);
float AD7414_Read_Temp(void);
void delay_usad7414(unsigned int delaytimes);

#endif