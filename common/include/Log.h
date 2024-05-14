/*************************************************************************
	> File Name: Log.h
	> Author: 
	> Mail: 
	> Created Time: Tue 14 May 2024 05:35:38 PM CST
 ************************************************************************/

#ifndef _LOG_H
#define _LOG_H


#include <stdio.h>
#include <time.h>
#include "./Utils.h"

#define LOG_EVENT_NORMAL 0
#define LOG_EVENT_WARNING 1
#define LOG_EVENT_ERROR 2

void log_event(const char *logfile, const int level, const char *msg);//打印日志信息


#endif
