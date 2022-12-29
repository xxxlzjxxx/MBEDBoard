/*****************************************************************************
** �ļ����ƣ�DELAY.h ����׼��ʱ������
** ��    �ܣ�
** �޸���־��
******************************************************************************/
#ifndef __DELAY_H
#define __DELAY_H

#define CPU_F  20000000

#define delay_us(x) 	__delay_cycles((long)(CPU_F*(double)x/1000000.0) )//x MHz----us
#define delay_ms(x) 	__delay_cycles((long)(CPU_F*(double)x/1000.0))
#define delay_s(x)      __delay_cycles((long)(CPU_F*(double)x/1.0))

#endif