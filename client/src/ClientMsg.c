/*************************************************************************
	> File Name: ClientMsg.c
	> Author: 
	> Mail: 
	> Created Time: Fri 17 May 2024 02:39:19 PM CST
 ************************************************************************/

#include "../common/include/Head.h"
#include "../include/ClientLog.h"


void recvMsg(int sockfd, struct SmhMsg *msg) {
    if (msg == 0 || sockfd < 0) return ;

    //获取消息：recv()
    ssize_t rsize = recv(sockfd, msg, sizeof(*msg), 0);//粘包、拆包
    if (rsize == -1) {
        PRINT(LOG_LEVEL_ERROR, "recvMsg 接收消息失败");
        close(sockfd);
        exit(EXIT_FAILURE);
    } else if (rsize == 0) {
        PRINT(LOG_LEVEL_NORMAL, "服务器正在关闭....");
        close(sockfd);
        exit(EXIT_SUCCESS);
    } 
    //解析消息: parseMsg()
    printMsg(msg);
    return NULL;
}


void parseMsg(struct SmhMsg *msg) {
    
    //TODO : d解析MSG结构体类型
    
    if (msg->type & SMH_HEART) {
        //TODO : 心跳信息，打印信息比响应心跳
        
    } else if (msg->type & SMH_MSG) {
        //TODO : 私聊信息， 打印信息

    } else if (msg->type & SMH_WALL) {
        //TODO : 公告信息, 打印信息

    } else if (msg->type & SMH_FIN) {
        //TODO : 服务器正要停止

        close(sockfd);
        exit(EXIT_SUCCESS);
    } else {
        //TODO : 不支持的消息类型

    }

    return ;
}


void printMsg(struct SmhMsg *msg) {
    if (msg == NULL) return ;
    parseMsg(msg);
    return ;
}


void inputMsg(int sockfd) {
    struct SmhMsg msg;
    memset(&msg, 0, sizeof(msg));
    send_chat(sockfd, &msg);
    return ;
}


void parseStr(char *str) {
    
    //TODO : 解析字符串

    return ;
}


void parseCtl(char *str, struct CTL *ctl) {
    //TODO : 解析指令

    return ;
}


void enscMsg(char *str, struct SmhMsg *msg) {
    //TODO : 封装结构体MSG
    return ;
} 

void sendMsg(struct SmhMsg *msg) {
    
    //TODO : 发送消息

}


