/*****************************************************************************
** �ļ����ƣ�eeprom.h   (оƬΪat24c512) 128�ֽ�ÿҳ ��64k 512ҳ
** ��    �ܣ�
** �޸���־��
******************************************************************************/
#ifndef __EEPROM_H
#define __EEPROM_H

/*****************************************************************************
** �ܽŶ���		AT24Cxx:    SDA ->P3.0, SCL->P3.1
*****************************************************************************/
#define   SDA_SEL_GPIO                  (P3SEL &=~BIT0)  //����ΪGPIO��
#define   SDA_DIR_OUTPUT                (P3DIR |= BIT0)  //�������
#define   SDA_OUT_HIGH                  (P3OUT |= BIT0)  //�����
#define   SDA_OUT_LOW                   (P3OUT &=~BIT0)  //�����

#define   SDA_DIR_INPUT                 (P3DIR &=~BIT0)  //����
#define   SDA_READ                      (P3IN & BIT0)      //���ܽŵ�ƽ״̬

#define   SCL_SEL_GPIO                  (P3SEL &=~BIT1)  //����ΪGPIO��
#define   SCL_DIR_OUTPUT                (P3DIR |= BIT1)  //�������
#define   SCL_OUT_HIGH                  (P3OUT |= BIT1)  //�����
#define   SCL_OUT_LOW                   (P3OUT &=~BIT1)  //�����

#define   WP_SEL_GPIO                  (P2SEL &=~BIT5)  //����ΪGPIO��
#define   WP_DIR_OUTPUT                (P2DIR |= BIT5)  //�������
#define   WP_OUT_HIGH                  (P2OUT |= BIT5)  //�����
#define   WP_OUT_LOW                   (P2OUT &=~BIT5)  //�����


/*******************************************************************************
** ��������
*******************************************************************************/
//void delay_us(unsigned int delaytimes);
void EepromSequentialRead(unsigned int page,unsigned char * buf,unsigned int len);
void EepromWritePage(unsigned int page,unsigned char * buf,unsigned char len);
unsigned char EepromByteRead(unsigned int page);
void EepromByteWrite(unsigned int page,unsigned char wdata);
void EepromWriteMorePage(unsigned int page,unsigned char * pbuf,unsigned int len);
void I2cInit(void);
#endif