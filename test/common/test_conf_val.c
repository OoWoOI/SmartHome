/*************************************************************************
	> File Name: test_conf_val.c
	> Author: 
	> Mail: 
	> Created Time: Tue 14 May 2024 09:38:38 AM CST
 ************************************************************************/

#include<stdio.h>
#include "../../common/include/Conf.h"

const char *path = "../../server/conf/server.ini";

int main() {
    char *IP = NULL;

    if  ((get_conf_val(path, "SERVER_IP", &IP)) < 0) {
        perror("get_conf_val");
        return -1;
    }

    char *PORT = NULL;

    if ((get_conf_val(path, "SERVER_PORT", &PORT)) < 0) {
        perror("get_conf_val");
        return -1;
    }

    printf("IP  = %s\n", IP);
    printf("PORT = %s\n", PORT);
    return 0;
}
