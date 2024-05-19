/*************************************************************************
	> File Name: Client.c
	> Author: 
	> Mail: 
	> Created Time: Fri 17 May 2024 02:36:01 PM CST
 ************************************************************************/


#include "../include/Client.h"

struct Client_Info clnInfo;

WINDOW *message_win, *message_sub,  *info_win, *input_win, *info_sub;

//初始化客户端
__attribute__((constructor))
void init_client() {

    //获取svrIp、svrPort
    clnInfo.svrIp = getSvrIp();
    clnInfo.svrPort = getSvrPort();
    //sockfd获取服务器连接
    if ((clnInfo.sockfd = socket_connect(clnInfo.svrIp, clnInfo.svrPort)) < 0) {
        PRINT(LOG_LEVEL_ERROR, "获取服务器连接失败");
        exit(EXIT_FAILURE);
    }

    //注册信号事件
    signal(SIGINT, logout);
    
    //初始化UI界面
    
    setlocale(LC_ALL, "");

    #ifndef _D
        init_ui();
    #endif 
    
    return ;
}

void *client_recv(void *arg) {
    struct SmhMsg msg;
    while (1) {
        memset(&msg, 0, sizeof(msg));
        recvMsg(clnInfo.sockfd, &msg);
    }
    
    return NULL;
}

void logout(int signum) {
    //TODO : 发送消息到服务器
    struct SmhMsg msg;
    //发送type为SMH_FIN的数据包
    msg.type = SMH_FIN;
    send(clnInfo.sockfd, &msg, sizeof(msg), 0);
    //关闭连接
    close(clnInfo.sockfd);
    DBG(RED"Bye!\\n"NONE);
    exit(EXIT_SUCCESS);
}

//启动客户端
int run_client() {
    
    //创建线程（接收消息）
    
    pthread_t recvThread;
    pthread_create(recvThread, NULL, client_recv, NULL);
    
    while (1) {//输入信息
        int c = getchar();
        switch (c) {
            case 13 : {
                inputMsg(clnInfo.sockfd);
            } break;
            default : {} break;
        }
        box(input_win, 0, 0);
        wrefresh(input_win);
    }


    return 0;
}
