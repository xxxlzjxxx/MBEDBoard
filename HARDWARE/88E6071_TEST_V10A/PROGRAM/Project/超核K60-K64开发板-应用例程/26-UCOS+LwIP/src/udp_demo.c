#include "includes.h"
#include <lwip/sockets.h>
#include <stdint.h>
#include <string.h>
  

#define UDP_PRIO                8
#define UDP_STK_SIZE            512
OS_STK UDP_TASK_STK[UDP_STK_SIZE];

#define UDP_PORT                7
#define BUFSZ                   64
uint8_t udp_demo_recvbuf[BUFSZ];


//udp������
static void udp_thread(void *arg)
{
    
    int sock;
    int bytes_read;
    char *recv_data;
    uint32_t addr_len;
    struct sockaddr_in server_addr, client_addr;
    
   recv_data = malloc(BUFSZ);

   if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
   {
       printf("Socket error\n");

       free(recv_data);
       return;
   }
   
   /* ��ʼ����������ַ */
   server_addr.sin_family = AF_INET;
   server_addr.sin_port = htons(UDP_PORT);
   server_addr.sin_addr.s_addr = INADDR_ANY;
   memset(&(server_addr.sin_zero),0, sizeof(server_addr.sin_zero));
   
   /* �� */
   if (bind(sock,(struct sockaddr *)&server_addr,
            sizeof(struct sockaddr)) == -1)
   {
       /* ��ʧ�� */
       printf("Bind error\n");
       free(recv_data);
       return;
   }
   
    addr_len = sizeof(struct sockaddr);
    printf("UDPServer Waiting for client on port %d...\n", UDP_PORT);
   
   while (1)
   {
       bytes_read = recvfrom(sock, recv_data, BUFSZ - 1, 0,
                             (struct sockaddr *)&client_addr, &addr_len);

       recv_data[bytes_read] = '\0';

       sendto(sock, recv_data, strlen(recv_data), 0,
              (struct sockaddr *)&client_addr, sizeof(struct sockaddr));
       
       printf("\n(%s , %d) said : ",inet_ntoa(client_addr.sin_addr),
                  ntohs(client_addr.sin_port));
       printf("%s", recv_data);

       if (strcmp(recv_data, "exit") == 0)
       {
           lwip_close(sock);

           free(recv_data);
           break;
       }
   }
   
    
}


uint8_t udp_server(void)
{
	INT8U res;
	OS_CPU_SR cpu_sr;
	
	OS_ENTER_CRITICAL();	//���ж�
	res = OSTaskCreate(udp_thread, (void*)0,(OS_STK*)&UDP_TASK_STK[UDP_STK_SIZE-1], UDP_PRIO); //����UDP�߳�
	OS_EXIT_CRITICAL();		//���ж�
	
	return res;
}

