/*****************************************************************************
** 文件名称：eeprom.h   (芯片为at24c512) 128字节每页 共64k 512页
** 功    能：
** 修改日志：
******************************************************************************/
#ifndef __EEPROM_H
#define __EEPROM_H

/*****************************************************************************
** 管脚定义		AT24Cxx:    SDA ->P3.0, SCL->P3.1
*****************************************************************************/
#define   SDA_SEL_GPIO                  (P3SEL &=~BIT0)  //设置为GPIO口
#define   SDA_DIR_OUTPUT                (P3DIR |= BIT0)  //方向输出
#define   SDA_OUT_HIGH                  (P3OUT |= BIT0)  //输出高
#define   SDA_OUT_LOW                   (P3OUT &=~BIT0)  //输出低

#define   SDA_DIR_INPUT                 (P3DIR &=~BIT0)  //输入
#define   SDA_READ                      (P3IN & BIT0)      //读管脚电平状态

#define   SCL_SEL_GPIO                  (P3SEL &=~BIT1)  //设置为GPIO口
#define   SCL_DIR_OUTPUT                (P3DIR |= BIT1)  //方向输出
#define   SCL_OUT_HIGH                  (P3OUT |= BIT1)  //输出高
#define   SCL_OUT_LOW                   (P3OUT &=~BIT1)  //输出低

#define   WP_SEL_GPIO                  (P2SEL &=~BIT5)  //设置为GPIO口
#define   WP_DIR_OUTPUT                (P2DIR |= BIT5)  //方向输出
#define   WP_OUT_HIGH                  (P2OUT |= BIT5)  //输出高
#define   WP_OUT_LOW                   (P2OUT &=~BIT5)  //输出低


/*******************************************************************************
** 函数声明
*******************************************************************************/
//void delay_us(unsigned int delaytimes);
void EepromSequentialRead(unsigned int page,unsigned char * buf,unsigned int len);
void EepromWritePage(unsigned int page,unsigned char * buf,unsigned char len);
unsigned char EepromByteRead(unsigned int page);
void EepromByteWrite(unsigned int page,unsigned char wdata);
void EepromWriteMorePage(unsigned int page,unsigned char * pbuf,unsigned int len);
void I2cInit(void);
#endif