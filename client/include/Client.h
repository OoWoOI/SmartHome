/*************************************************************************
	> File Name: client.h
	> Author: 
	> Mail: 
	> Created Time: Mon 13 May 2024 10:28:06 PM CST
 ************************************************************************/

#ifndef _CLIENT_H
#define _CLIENT_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include "./ClientMSG.h"
#include "./ClientSignal.h"
#include "../common/include/NetWork.h"
#include "./ClientConf.h"
#include "./ClientLog.h"
#include "../common/include/DataTypes.h"

struct Client_Info {
    char *server_ip;
    int server_port;
    int sockfd;
};

int client_run();

#endif
