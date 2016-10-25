

#include        "includes.h"

#define PI 3.1415926535897932384626433832795028841971	//定义圆周率值
#define FFT_N 512								//定义FFT的点数
/********************************以下为第一种FFT运算***************************/
// float max = 0, sum = 0;
/*************************************************************************
** Name:		复数运算函数
** Workspace: 	IAR 6.10 
** Designed by:	xxxlzjxxx
** Date: 		2015.07.31
** Function:	c_abs	复数取模
				c_plus	
				c_sub
				c_mul
				c_div
				Wn_i
** Version:	
*************************************************************************/
void c_abs(struct _Compx f[],float out[],int n)  
{  
  	int i = 0;  
  	float t;  
  	for(i=0;i<n;i++)  
  	{  
    	t = f[i].real * f[i].real + f[i].imag * f[i].imag;  
    	out[i] = sqrt(t);  
  	}   
}    
void c_plus(struct _Compx a,struct _Compx b,struct _Compx *c)  
{  
  	c->real = a.real + b.real;  
  	c->imag = a.imag + b.imag;  
}   
void c_sub(struct _Compx a,struct _Compx b,struct _Compx *c)  
{  
  	c->real = a.real - b.real;  
  	c->imag = a.imag - b.imag;   
}  
void c_mul(struct _Compx a,struct _Compx b,struct _Compx *c)  
{  
  	c->real = a.real * b.real - a.imag * b.imag;  
  	c->imag = a.real * b.imag + a.imag * b.real;     
}  
void c_div(struct _Compx a,struct _Compx b,struct _Compx *c)  
{  
  	c->real = (a.real * b.real + a.imag * b.imag)/(b.real * b.real +b.imag * b.imag);  
  	c->imag = (a.imag * b.real - a.real * b.imag)/(b.real * b.real +b.imag * b.imag);  
}
//void Wn_i(int n,int i,struct _Compx *Wn,char flag)  
//{  
//  	Wn->real = cos(2*PI*i/n);  
//  	if(flag == 1)  
//  	Wn->imag = -sin(2*PI*i/n);  
//  	else if(flag == 0)  
//  	Wn->imag = -sin(2*PI*i/n);  
//}
struct _Compx EE(struct _Compx a1, struct _Compx b1)
{
	struct _Compx c1;
	c1.real=a1.real*b1.real-a1.imag*b1.imag;
	c1.imag=a1.real*b1.imag+a1.imag*b1.real;
	return(c1);
}
/*************************************************************************
** Name:		void fft(struct _Compx *x, int Num) 
** Workspace: 	IAR 6.10 
** Designed by:	xxxlzjxxx
** Date: 		2015.07.31
** Function:	对结构体数组x[i]做Num点FFT
** Version:	
*************************************************************************/
void FFT(struct _Compx *x, int Num)  
{  
    int i,j,l,k,ip;  
    static int M = 0;  
    static int le,le2;  
    double sR,sI,tR,tI,uR,uI;  
  
    M = (int)(log(Num) / log(2));  
  
    /* 
     * bit reversal sorting 
     */  
    l = Num / 2;  
    j = l;  
    //BitReverse(x,x,N,M);  
    for (i=1; i<=Num-2; i++) {  
        if (i < j) {  
            tR = x[j].real;  
            tI = x[j].imag;  
            x[j].real = x[i].real;  
            x[j].imag = x[i].imag;  
            x[i].real = tR;  
            x[i].imag = tI;  
        }  
        k = l;  
        while (k <= j) {  
            j = j - k;  
            k = k / 2;  
        }  
        j = j + k;  
    }  
  
    /* 
     * For Loops 
     */  
    for (l=1; l<=M; l++) {   /* loop for ceil{log2(N)} */  
        le = (int)pow(2,l);  
        le2 = (int)(le / 2);  
        uR = 1;  
        uI = 0;  
        sR = cos(PI / le2);  
        sI = -sin(PI / le2);  
        for (j=1; j<=le2; j++) {   /* loop for each sub DFT */  
            //jm1 = j - 1;  
            for (i=j-1; i<=Num-1; i+=le) {  /* loop for each butterfly */  
                ip = i + le2;  
                tR = x[ip].real * uR - x[ip].imag * uI;  
                tI = x[ip].real * uI + x[ip].imag * uR;  
                x[ip].real = x[i].real - tR;  
                x[ip].imag = x[i].imag - tI;  
                x[i].real += tR;  
                x[i].imag += tI;  
            }  /* Next i */  
            tR = uR;  
            uR = tR * sR - uI * sI;  
            uI = tR * sI + uI *sR;  
        } /* Next j */  
    } /* Next l */   
} 
/******************************************************************************
** 函数名称： void FFT(struct compx *xin,int N)
** 功    能:  FFT变换
** 修改日志：
******************************************************************************/
void fft(struct _Compx *xin, int Num) //*xin为需要FFT变换的数组，Num为转换的点数
{
    int f, m, LH, nm, i, k, j, L;
    double p, ps;
    long int le, B, ip;
    float pi;
    struct _Compx w, t;

    LH=Num>>1;
    f=Num;
    for(m=1;(f=f>>1)!=1;m++){;}
    nm=Num-2;    
    j=Num>>1;
 
    for(i=1;i<=nm;i++)        //  变址运算
    {
        if(i<j){t=xin[j];xin[j]=xin[i];xin[i]=t;}
        k=LH;
        while(j>=k){j=j-k;k=k/2;}
        j=j+k;
    }
    
    for(L=1;L<=m;L++)       //实现蝶形运算
    {  
        le=(long int)pow(2,L);
        B=le>>1; 
        pi=3.1415926;
        
        for(j=0;j<=B-1;j++)
        {
            p=pow(2,m-L)*j;
            ps=2*pi/N*p;
            w.real=cos(ps);
            w.imag=-sin(ps);
            
            for(i=j;i<=N-1;i=i+le)
            { 
                ip=i+B;
                t=EE(xin[ip],w);
                xin[ip].real=xin[i].real-t.real;
                xin[ip].imag=xin[i].imag-t.imag;
                xin[i].real=xin[i].real+t.real;
                xin[i].imag=xin[i].imag+t.imag;
            }
        }
    }
}
/******************************************************************************
** 函数名称： float  THDcount(unsigned int *result)
** 功    能:  失真度计算(注意函数中FFT点数的修改)
** 修改日志：
******************************************************************************/
//float  THDcount(double *result)
//{
//    unsigned int i = 0, n = 2, m, t = 0;
//    float THD = 0;
//    max = result[1];
//    for(i = 2; i < 512; i++)
//    {
//      	if(result[i] > max)
//      	{
//        	max = result[i];
//        	t = i;
//      	}
//    }
//    m = t * n;
//    while(m < 512)
//    {
//        sum = result[m] * result[m] + sum;
//        n++;
//        m = t * n;
//    }
//    sum = sum / (max * max);
//    THD = 100 * sqrt(sum);	
//    return THD;
//}
/********************************以下为第二种FFT运算***************************/

/******************************************************************************
** 函数名称： 	void kkfft(double pr[], double pi[], int n, int k, double fr[], double fi[], int l, int il)
** 功    能:  	FFT
** 例如：		kkfft(s1, s2, 128, 7, s3, s4, 0, 1);
** 说明			s1对应ad才来的值，s2是ad采样的虚部一般为0，128采样点数一定要是2的n次方，
				7就是那个n了，s3，s4背管了是副角返回值，0,1是程序内定的标志。
** 意义：		fft结果的意义：一个数组如S1[n],那么 s1[0]/采样点数 是直流分量值，
				而实际信号的频率在数组中的反应是 f=n*采样频率/采样点数；
** 修改日志：
******************************************************************************/
//void kkfft(double pr[], double pi[], int n, int k, double fr[], double fi[], int l, int il)
//{
//    int it,m,is,i,j,nv,l0;
//    double p,q,s,vr,vi,poddr,poddi;
//    for (it=0; it<=n-1; it++)
//    {
//        m = it;
//        is = 0;
//        for (i=0; i<=k-1; i++)
//        {
//            j = m/2;
//            is = 2*is+(m-2*j);
//            m = j;
//        }
//        fr[it] = pr[is];
//        fi[it] = pi[is];
//    }
//
//    pr[0] = 1.0;
//    pi[0] = 0.0;
//    p = 6.283185306/(1.0*n);		//6.283185306 = 2 * pi;
//    pr[1] = cos(p);
//    pi[1] = -sin(p);
//
//    if (l!=0)
//        pi[1]=-pi[1];
//
//    for (i=2; i<=n-1; i++)
//    {
//        p = pr[i-1]*pr[1];
//        q = pi[i-1]*pi[1];
//        s = (pr[i-1]+pi[i-1])*(pr[1]+pi[1]);
//        pr[i] = p-q;
//        pi[i] = s-p-q;
//    }
//	
//    for (it=0; it<=n-2; it=it+2)
//    {
//        vr = fr[it];
//        vi = fi[it];
//        fr[it] = vr+fr[it+1];
//        fi[it] = vi+fi[it+1];
//        fr[it+1] = vr-fr[it+1];
//        fi[it+1] = vi-fi[it+1];
//    }
//    m = n/2;
//    nv = 2;
//	
//    for (l0=k-2; l0>=0; l0--)
//    {
//        m = m/2;
//        nv = 2*nv;
//        for (it=0; it<=(m-1)*nv; it=it+nv)
//            for (j=0; j<=(nv/2)-1; j++)
//            {
//                p = pr[m*j]*fr[it+j+nv/2];
//                q = pi[m*j]*fi[it+j+nv/2];
//                s = pr[m*j]+pi[m*j];
//                s = s*(fr[it+j+nv/2]+fi[it+j+nv/2]);
//                poddr = p-q;
//                poddi = s-p-q;
//                fr[it+j+nv/2] = fr[it+j]-poddr;
//                fi[it+j+nv/2] = fi[it+j]-poddi;
//                fr[it+j] = fr[it+j]+poddr;
//                fi[it+j] = fi[it+j]+poddi;
//            }
//    }
//
//    if (l!=0)
//    {
//        for (i=0; i<=n-1; i++)
//        {
//            fr[i] = fr[i]/(1.0*n);
//            fi[i] = fi[i]/(1.0*n);
//        }
//    }
//    if (il!=0)
//    {
//        for (i=0; i<=n-1; i++)
//        {
//            pr[i] = sqrt(fr[i]*fr[i]+fi[i]*fi[i]);
//            if (fabs(fr[i])<0.000001*fabs(fi[i]))
//            {
//                if ((fi[i]*fr[i])>0)
//                    pi[i] = 90.0;
//                else
//                    pi[i] = -90.0;
//            }
//            else
//                pi[i] = atan(fi[i]/fr[i])*360.0/6.283185306;
//        }
//    }
//    return;
//}