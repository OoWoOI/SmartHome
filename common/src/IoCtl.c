/*************************************************************************
	> File Name: IoCtl.c
	> Author: 
	> Mail: 
	> Created Time: Mon 13 May 2024 10:22:42 PM CST
 ************************************************************************/

#include "../include/IoCtl.h"

//设置fd非阻塞IO
int make_nonblock(int fd) {
    int flag;
    if ((flag = fcntl(fd, F_GETFL)) < 0) {
        return -1;
    }
    
    flag |= O_NONBLOCK;
    
    return fcntl(fd, F_SETFL, flag);
}

//设置fd为阻塞IO
int make_block(int fd) {
    int flag;
    if ((flag = fcntl(fd, F_GETFL)) < 0) {
        return -1;
    }
    flag &= ~O_NONBLOCK;
    return fcntl(fd, F_SETFL, flag);
}

