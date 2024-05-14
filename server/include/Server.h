/*************************************************************************
	> File Name: server.h
	> Author: 
	> Mail: 
	> Created Time: Mon 13 May 2024 10:32:30 PM CST
 ************************************************************************/

#ifndef _SERVER_H
#define _SERVER_H

#include <stdio.h>
#include "../common/include/Conf.h"
#include "../include/ServerConf.h"

#define CONF_PATH "./conf/server.ini"

typedef struct Server {
    int port;
    int conns;//最大连接数
    int sockfd;//socket套接字
}SVR;

int server_run();//启动服务端



#endif