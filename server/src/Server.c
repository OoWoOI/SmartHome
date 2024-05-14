/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: Mon 13 May 2024 10:33:24 PM CST
 ************************************************************************/

#include "../include/Server.h"



SVR svr;//服务端实例

__attribute__((constructor)) 
void server_init() {
    DBG("Server Init.....\n");
    svr.port = GetPort(CONF_PATH);
    svr.conns = GetConns(CONF_PATH);
    return ;
}

int server_run() {
    

    

    
    
    return 0;
}
