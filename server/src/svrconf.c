/*************************************************************************
	> File Name: ServerConf.c
	> Author: 
	> Mail: 
	> Created Time: Tue 14 May 2024 10:31:07 AM CST
 ************************************************************************/

#include "../common/include/head.h"
#include "../include/svrConf.h"
#include "../include/svrLog.h"

int getSvrPort() {
    char *confVal = NULL;
    int ret;
    if ((ret = get_conf_val(SVRCONF, "SERVER_PORT", &confVal)) != SUCCESS) {
        switch (ret) {
            case FILE_NOT_EXIST: {
                PRINT(LOG_LEVEL_ERROR, "Get Conf Val SERVER_PORT But FILE_NOT_EXIST");
            } break;
            case KEY_NOT_EXIST: {
                PRINT(LOG_LEVEL_ERROR, "Get Conf Val SERVER_PORT But KEY_NOT_EXIST");
            } break;
            default : {
                PRINT(LOG_LEVEL_ERROR, "Get Conf Val SERVER_PORT But UNKNOW ERROR");
            } break;
        }
        exit(-1);
    } 
    
   return atoi(confVal); 
}

int getSvrConns() {
    char *confVal = NULL;
    int ret;
    if ((ret = get_conf_val(SVRCONF, "SERVER_CONNS", &confVal)) != SUCCESS) {
        switch (ret) {
            case FILE_NOT_EXIST: {
                PRINT(LOG_LEVEL_ERROR, "Get Conf Val SERVER_CONNS But FILE_NOT_EXIST");
            } break;
            case KEY_NOT_EXIST: {
                PRINT(LOG_LEVEL_ERROR, "Get Conf Val SERVER_CONNS But KEY_NOT_EXIST");
            } break;
            default : {
                PRINT(LOG_LEVEL_ERROR, "Get Conf Val SERVER_CONNS But UNKNOW ERROR");
            } break;
        }
        exit(-1);
    } 
    
   return atoi(confVal); 
}





