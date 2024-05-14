/*************************************************************************
	> File Name: NetWork.h
	> Author: 
	> Mail: 
	> Created Time: Mon 13 May 2024 10:21:13 PM CST
 ************************************************************************/

#ifndef _NETWORK_H
#define _NETWORK_H


#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>

int socket_create(const int port);
int socket_connect(const char *ip, int port);

#endif
