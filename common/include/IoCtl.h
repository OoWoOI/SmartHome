/*************************************************************************
	> File Name: IoCtl.h
	> Author: 
	> Mail: 
	> Created Time: Mon 13 May 2024 10:21:29 PM CST
 ************************************************************************/

#ifndef _IOCTL_H
#define _IOCTL_H

#include <fcntl.h>

int make_nonblock(int fd);
int make_block(int fd);

#endif
