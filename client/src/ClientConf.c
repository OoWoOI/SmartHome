/*************************************************************************
	> File Name: ClientConf.c
	> Author: 
	> Mail: 
	> Created Time: Fri 17 May 2024 03:05:01 PM CST
 ************************************************************************/


#include "../common/include/Head.h"
#include "../include/ClientConf.h"
#include "../include/ClientLog.h"

int getSvrPort() {
    char *confVal = NULL; 
    int ret;
    if ((ret = get_conf_val(CLNCONF, "SERVER_PORT", &confVal)) < 0) {
        switch (ret) {
            case FILE_NOT_EXIST : {
                PRINT(LOG_LEVEL_ERROR, "get cln server port but file not exist");
            } break;
            case KEY_NOT_EXIST : {
                PRINT(LOG_LEVEL_ERROR, "get cln server port but key not exist");
            } break;
            default : {
                PRINT(LOG_LEVEL_ERROR , "get cln server port but unknow error"); 
            } break;
        }
        exit(EXIT_FAILURE);
    }
    return atoi(confVal);
}

char *getSvrIp() {
    char *confVal = NULL; 
    int ret;
    if ((ret = get_conf_val(CLNCONF, "SERVER_IP", &confVal)) < 0) {
        switch (ret) {
            case FILE_NOT_EXIST : {
                PRINT(LOG_LEVEL_ERROR , "get cln server ip but file not exist");
            } break;
            case KEY_NOT_EXIST : {
                PRINT(LOG_LEVEL_ERROR ,"get cln server ip but key not exist");
            } break;
            default : {
                PRINT(LOG_LEVEL_ERROR , "get cln server ip but unknow error"); 
            } break;
        }
        exit(EXIT_FAILURE);
    }
    return confVal;
}
