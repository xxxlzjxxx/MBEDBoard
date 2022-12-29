#ifndef __FFT_H
#define __FFT_H

struct _Compx 
{
    double real;
    double imag;
};

//��������
//******************************************************************************
void c_plus(struct _Compx a, struct _Compx b, struct _Compx *c);//������  
void c_mul(struct _Compx a, struct _Compx b, struct _Compx *c) ;//������  
void c_sub(struct _Compx a, struct _Compx b, struct _Compx *c); //��������  
void c_div(struct _Compx a, struct _Compx b, struct _Compx *c); //��������     
void c_abs(struct _Compx f[], float out[],int n);//��������ȡģ
struct _Compx EE(struct _Compx a1, struct _Compx b1);
void FFT(struct _Compx *x, int Num);//����Ҷ�任 ���Ҳ��������x��
//float  THDcount(double *result);
//******************************************************************************
//void kfft(double *pr, int n, int k);
void fft(struct _Compx *xin, int Num);


#endif