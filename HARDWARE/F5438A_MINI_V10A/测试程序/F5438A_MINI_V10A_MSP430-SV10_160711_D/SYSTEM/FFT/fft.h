#ifndef __FFT_H
#define __FFT_H

struct _Compx 
{
    double real;
    double imag;
};

//函数申明
//******************************************************************************
void c_plus(struct _Compx a, struct _Compx b, struct _Compx *c);//复数加  
void c_mul(struct _Compx a, struct _Compx b, struct _Compx *c) ;//复数乘  
void c_sub(struct _Compx a, struct _Compx b, struct _Compx *c); //复数减法  
void c_div(struct _Compx a, struct _Compx b, struct _Compx *c); //复数除法     
void c_abs(struct _Compx f[], float out[],int n);//复数数组取模
struct _Compx EE(struct _Compx a1, struct _Compx b1);
void FFT(struct _Compx *x, int Num);//傅立叶变换 输出也存在数组x中
//float  THDcount(double *result);
//******************************************************************************
//void kfft(double *pr, int n, int k);
void fft(struct _Compx *xin, int Num);


#endif