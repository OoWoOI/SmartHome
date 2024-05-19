/*************************************************************************
	> File Name: Client.h
	> Author: 
	> Mail: 
	> Created Time: Fri 17 May 2024 02:32:55 PM CST
 ************************************************************************/

#ifndef _CLIENT_H
#define _CLIENT_H

#include "../common/include/Head.h"
#include "./ClientConf.h"
#include "./ClientLog.h"

//客户端基本信息
struct Client_Info {
    char *svrIp;
    int svrPort;
    int sockfd;
};

int run_client();



#endif
