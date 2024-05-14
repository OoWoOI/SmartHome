/*************************************************************************
	> File Name: ServerConf.c
	> Author: 
	> Mail: 
	> Created Time: Tue 14 May 2024 10:31:07 AM CST
 ************************************************************************/

#include "../include/ServerConf.h"

int GetPort(const char *path) {
    char *confVal = NULL;
    int ret;
    if ((ret = get_conf_val(path, "SERVER_PORT", &confVal)) != SUCCESS) {
        switch (ret) {
            case FILE_NOT_EXIST: {
                DBG("Get Conf Val SERVER_PORT But FILE_NOT_EXIST\n");
            } break;
            case KEY_NOT_EXIST: {
                DBG("Get Conf Val SERVER_PORT But KEY_NOT_EXIST\n");
            } break;
            default : {
                DBG("Get Conf Val SERVER_PORT But UNKNOW ERROR\n");
            } break;
        }
        exit(-1);
    } 
    
   return atoi(confVal); 
}

int GetConns(const char *path) {
    char *confVal = NULL;
    int ret;
    if ((ret = get_conf_val(path, "SERVER_CONNS", &confVal)) != SUCCESS) {
        switch (ret) {
            case FILE_NOT_EXIST: {
                DBG("Get Conf Val SERVER_CONNS But FILE_NOT_EXIST\n");
            } break;
            case KEY_NOT_EXIST: {
                DBG("Get Conf Val SERVER_CONNS But KEY_NOT_EXIST\n");
            } break;
            default : {
                DBG("Get Conf Val SERVER_CONNS But UNKNOW ERROR\n");
            } break;
        }
        exit(-1);
    } 
    
   return atoi(confVal); 
}





