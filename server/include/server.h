/*************************************************************************
	> File Name: server.h
	> Author: 
	> Mail: 
	> Created Time: Mon 13 May 2024 10:32:30 PM CST
 ************************************************************************/

#ifndef _SERVER_H
#define _SERVER_H


#include "../common/include/head.h"
#include "./svrConf.h"
#include "./svrLog.h"




#define CONF_PATH "./conf/server.ini"
#define MAX_CLIENTS 100
#define HEARTBEAT_INTERVAL 5
#define MAX_EVENTS 10


typedef struct {
    int epoll_fd;
    int clients[MAX_CLIENTS];
    int client_count;
    pthread_mutex_t client_mutex;
    pthread_t heartbeat_thread;
} SubReactor;

typedef struct {
    int epoll_fd;
    int timer_fd;
    SubReactor sub_reactor;
} MainReactor;


int server_run();
void main_reactor_init(MainReactor *main_reactor);
void main_reactor_run(MainReactor *main_reactor, int listen_fd);
void handle_new_connection(MainReactor *main_reactor, int listen_fd);
void handle_client_event(int client_fd);
void *heartbeat_thread(void *arg);
void sub_reactor_run(SubReactor *sub_reactor);

#endif
