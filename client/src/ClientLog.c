/*************************************************************************
	> File Name: ClientLog.c
	> Author: 
	> Mail: 
	> Created Time: Wed 15 May 2024 08:40:45 AM CST
 ************************************************************************/

#include "../include/ClientLog.h"


void PRINT(const int level, const char *msg) {
    log_event(LOGFILE, level, msg);
    return ;
}
