/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: Mon 13 May 2024 10:29:20 PM CST
 ************************************************************************/

#include "../include/Client.h"


struct Client_Info cln;//客户端结构体

__attribute__((constructor))
void client_init() {
    printf("Client Init ....\n");
    cln.server_ip = Get_Server_Ip();
    cln.server_port = Get_Server_Port();
    
    return ;
}


int client_run() {
    signal(SIGINT, logout);//注册ctrl + c信号事件
    
    //获取连接
    if ((cln.sockfd = socket_connect(cln.server_ip, cln.server_port)) < 0) {
        PRINT(LOG_EVENT_ERROR, "获取服务器连接失败");
        return cln.sockfd;
    }

    pthread_t recvThread, sendThread;

    pthread_create(&recvThread, NULL, recv_MSG, NULL);
    pthread_create(&sendThread, NULL, send_MSG, NULL);
    
    pthread_join(recvThread, NULL); 
    pthread_join(sendThread, NULL); 

    return 0;
}
