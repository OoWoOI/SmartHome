/*************************************************************************
	> File Name: ServerConf.h
	> Author: 
	> Mail: 
	> Created Time: Tue 14 May 2024 10:32:15 AM CST
 ************************************************************************/

#ifndef _SERVERCONF_H
#define _SERVERCONF_H


#include "../../common/include/Utils.h"
#include "../../common/include/RetVal.h"
#include "../../common/include/Conf.h"

int GetPort(const char *path);//获取端口号
int GetConns(const char *path);//获取最大连接数



#endif
