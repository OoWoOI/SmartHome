/*************************************************************************
	> File Name: ClientConf.c
	> Author: 
	> Mail: 
	> Created Time: Wed 15 May 2024 08:40:36 AM CST
 ************************************************************************/

#include "../include/ClientConf.h"

char *Get_Server_Ip() {
    char *confVal = NULL;
    int ret;
    if ((ret = get_conf_val(LOGFILE, "SERVER_IP", &confVal)) != SUCCESS) {
        switch (ret) {
            case FILE_NOT_EXIST: {
                DBG("Get Conf Val SERVER_IP But FILE_NOT_EXIST\n");
            } break;
            case KEY_NOT_EXIST: {
                DBG("Get Conf Val SERVER_IP But KEY_NOT_EXIST\n");
            } break;
            default : {
                DBG("Get Conf Val SERVER_IP But UNKNOW ERROR\n");
            } break;
        }
        exit(-1);
    } 
    return confVal;
}


int Get_Server_Port() {
    char *confVal = NULL;
    int ret;
    if ((ret = get_conf_val(LOGFILE, "SERVER_PORT", &confVal)) != SUCCESS) {
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
