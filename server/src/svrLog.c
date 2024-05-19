/*************************************************************************
	> File Name: ServerLog.c
	> Author: 
	> Mail: 
	> Created Time: Tue 14 May 2024 05:34:25 PM CST
 ************************************************************************/

#include "../common/include/head.h"
#include "../include/svrLog.h"


void PRINT(const int level, const char *msg) {
    log_event(LOGFILE, level, msg);
    return ;
}
