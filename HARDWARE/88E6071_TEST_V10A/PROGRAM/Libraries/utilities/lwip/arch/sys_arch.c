/*
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 */
/* lwIP includes. */
#include "lwip/debug.h"
#include "lwip/def.h"
#include "lwip/sys.h"
#include "lwip/mem.h"

#include <stdint.h>

#ifdef USE_RTOS



//����Ϣָ��Ϊ��ʱ,ָ��һ������pvNullPointer��ָ���ֵ.
//��UCOS�����OSQPost()�е�msg==NULL�᷵��һ��OS_ERR_POST_NULL
//����,����lwip�л����sys_mbox_post(mbox,NULL)����һ������Ϣ,����
//�ڱ������а�NULL���һ������ָ��0Xffffffff
const void * const pvNullPointer = (mem_ptr_t*)0xffffffff;
 

err_t sys_mbox_new( sys_mbox_t *mbox, int size)
{
    (*mbox) = malloc(sizeof(TQ_DESCR));
    memset((*mbox),0,sizeof(TQ_DESCR));
    
	if(*mbox)
	{
		if(size > MAX_QUEUE_ENTRIES)
        {
            size=MAX_QUEUE_ENTRIES;
        }
 		(*mbox)->pQ = OSQCreate(&((*mbox)->pvQEntries[0]), size);  //ʹ��UCOS����һ����Ϣ����
		LWIP_ASSERT("OSQCreate",(*mbox)->pQ!=NULL); 
		if((*mbox)->pQ != NULL)
        {
            return ERR_OK;
        }
		else
		{ 
			free((*mbox));
			return ERR_MEM;
		}
	}
    else return ERR_MEM;
} 

void sys_mbox_free(sys_mbox_t * mbox)
{
	u8_t ucErr;
	(void)OSQDel((*mbox)->pQ, OS_DEL_ALWAYS, &ucErr);
	LWIP_ASSERT( "OSQDel ",ucErr == OS_ERR_NONE ); 
	free((*mbox)); 
	*mbox=NULL;
}

void sys_mbox_post(sys_mbox_t *mbox,void *msg)
{    
	if(msg == NULL)
    {
        msg=(void*)&pvNullPointer;//��msgΪ��ʱ msg����pvNullPointerָ���ֵ 
    }
    while(OSQPost((*mbox)->pQ,msg) != OS_ERR_NONE);
}

//������һ����Ϣ���䷢����Ϣ
//�˺��������sys_mbox_post����ֻ����һ����Ϣ��
//����ʧ�ܺ󲻻᳢�Եڶ��η���
//*mbox:��Ϣ����
//*msg:Ҫ���͵���Ϣ
//����ֵ:ERR_OK,����OK
// 	     ERR_MEM,����ʧ��
err_t sys_mbox_trypost(sys_mbox_t *mbox, void *msg)
{ 
	if(msg == NULL)
    {
        msg=(void*)&pvNullPointer;//��msgΪ��ʱ msg����pvNullPointerָ���ֵ 
    }
	if((OSQPost((*mbox)->pQ, msg)) != OS_ERR_NONE)
    {
       return ERR_MEM;
    }
	return ERR_OK;
}

//�ȴ������е���Ϣ
//*mbox:��Ϣ����
//*msg:��Ϣ
//timeout:��ʱʱ�䣬���timeoutΪ0�Ļ�,��һֱ�ȴ�
//����ֵ:��timeout��Ϊ0ʱ����ɹ��Ļ��ͷ��صȴ���ʱ�䣬
//		ʧ�ܵĻ��ͷ��س�ʱSYS_ARCH_TIMEOUT
u32_t sys_arch_mbox_fetch(sys_mbox_t *mbox, void **msg, u32_t timeout)
{ 
	u8_t ucErr;
	u32_t ucos_timeout,timeout_new;
	void *temp;
	sys_mbox_t m_box=*mbox;
	if(timeout!=0)
	{
		ucos_timeout=(timeout*OS_TICKS_PER_SEC)/1000; //ת��Ϊ������,��ΪUCOS��ʱʹ�õ��ǽ�����,��LWIP����ms
		if(ucos_timeout<1)ucos_timeout=1;//����1������
	}else ucos_timeout = 0; 
	timeout = OSTimeGet(); //��ȡϵͳʱ�� 
	temp=OSQPend(m_box->pQ,(u16_t)ucos_timeout,&ucErr); //������Ϣ����,�ȴ�ʱ��Ϊucos_timeout
	if(msg!=NULL)
	{	
		if(temp==(void*)&pvNullPointer)*msg = NULL;   	//��Ϊlwip���Ϳ���Ϣ��ʱ������ʹ����pvNullPointerָ��,�����ж�pvNullPointerָ���ֵ
 		else *msg=temp;									//�Ϳ�֪�����󵽵���Ϣ�Ƿ���Ч
	}    
	if(ucErr==OS_ERR_TIMEOUT)timeout=SYS_ARCH_TIMEOUT;  //����ʱ
	else
	{
		LWIP_ASSERT("OSQPend ",ucErr==OS_ERR_NONE); 
		timeout_new=OSTimeGet();
		if (timeout_new>timeout) timeout_new = timeout_new - timeout;//���������Ϣ��ʹ�õ�ʱ��
		else timeout_new = 0xffffffff - timeout + timeout_new; 
		timeout=timeout_new*1000/OS_TICKS_PER_SEC + 1; 
	}
	return timeout; 
}

u32_t sys_arch_mbox_tryfetch(sys_mbox_t *mbox, void **msg)
{
	return sys_arch_mbox_fetch(mbox, msg, 1);
}

int sys_mbox_valid(sys_mbox_t *mbox)
{  
	u8_t ucErr;
	int ret;
	OS_Q_DATA q_data;
	memset(&q_data, 0, sizeof(OS_Q_DATA));
	ucErr = OSQQuery ((*mbox)->pQ,&q_data);
	ret=(ucErr<2 && (q_data.OSNMsgs<q_data.OSQSize))?1:0;
	return ret; 
} 

void sys_mbox_set_invalid(sys_mbox_t *mbox)
{
	*mbox = NULL;
} 

err_t sys_sem_new(sys_sem_t * sem, u8_t count)
{  
	*sem = OSSemCreate((u16_t)count);
	if(*sem == NULL)
    {
        return ERR_MEM; 
    }
	return ERR_OK;
} 
//�ȴ�һ���ź���
//*sem:Ҫ�ȴ����ź���
//timeout:��ʱʱ��
//����ֵ:��timeout��Ϊ0ʱ����ɹ��Ļ��ͷ��صȴ���ʱ�䣬
//		ʧ�ܵĻ��ͷ��س�ʱSYS_ARCH_TIMEOUT
u32_t sys_arch_sem_wait(sys_sem_t *sem, u32_t timeout)
{ 
	u8_t ucErr;
	u32_t ucos_timeout, timeout_new; 
	if(	timeout!=0) 
	{
		ucos_timeout = (timeout * OS_TICKS_PER_SEC) / 1000;//ת��Ϊ������,��ΪUCOS��ʱʹ�õ��ǽ�����,��LWIP����ms
		if(ucos_timeout < 1)
		ucos_timeout = 1;
	}else ucos_timeout = 0; 
	timeout = OSTimeGet();  
	OSSemPend (*sem,(u16_t)ucos_timeout, (u8_t *)&ucErr);
 	if(ucErr == OS_ERR_TIMEOUT)timeout=SYS_ARCH_TIMEOUT;//����ʱ	
	else
	{     
 		timeout_new = OSTimeGet(); 
		if (timeout_new>=timeout) timeout_new = timeout_new - timeout;
		else timeout_new = 0xffffffff - timeout + timeout_new;
 		timeout = (timeout_new*1000/OS_TICKS_PER_SEC + 1);//���������Ϣ��ʹ�õ�ʱ��(ms)
	}
	return timeout;
}

void sys_sem_signal(sys_sem_t *sem)
{
	OSSemPost(*sem);
}

void sys_sem_free(sys_sem_t *sem)
{
	u8_t ucErr;
	(void)OSSemDel(*sem,OS_DEL_ALWAYS,&ucErr);
	if(ucErr != OS_ERR_NONE)
    {
        LWIP_ASSERT("OSSemDel ",ucErr==OS_ERR_NONE);
    }
	*sem = NULL;
} 

int sys_sem_valid(sys_sem_t *sem)
{
	OS_SEM_DATA  sem_data;
	return (OSSemQuery (*sem,&sem_data) == OS_ERR_NONE )? 1:0;              
} 

void sys_sem_set_invalid(sys_sem_t *sem)
{
	*sem = NULL;
} 

void sys_init(void)
{ 

}

OS_STK TCPIP_THREAD_TASK_STK[1024];
sys_thread_t sys_thread_new(const char *name, lwip_thread_fn thread, void *arg, int stacksize, int prio)
{
	//OS_CPU_SR cpu_sr;
	if(strcmp(name,TCPIP_THREAD_NAME) == 0)
	{
		OSTaskCreate(thread,arg, &TCPIP_THREAD_TASK_STK[stacksize-1], prio);
	} 
	return 0;
} 


u32_t sys_now(void)
{
	return (OSTimeGet()*1000/OS_TICKS_PER_SEC+1);
}

#else

static uint32_t lwip_timer;//lwip����ʱ�������,��λ:ms

void PIT_ISR(void)
{
    lwip_timer++;
}

u32_t sys_now(void)
{
	return lwip_timer*10;
}

//u8_t timer_expired(u32_t *last_time, u32_t tmr_interval)
//{
//    u32_t time;
//    time = *last_time;	
//    if((lwip_timer - time) >= tmr_interval)
//    {
//        *last_time = lwip_timer;
//        return 1;
//    }
//	return 0;
//}

#endif


