/*************************************************************************
	> File Name: ClientLog.c
	> Author: 
	> Mail: 
	> Created Time: Fri 17 May 2024 03:25:24 PM CST
 ************************************************************************/

#include "../common/include/Head.h"
#include "../include/ClientLog.h"


void PRINT(const int level, const char *msg) {
    //TODO : 客户端打印日志信息
    log_event(CLNLOG, level, msg);
    return ;
}
