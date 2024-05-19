/*************************************************************************
	> File Name: Head.h
	> Author: 
	> Mail: 
	> Created Time: Fri 17 May 2024 02:27:23 PM CST
 ************************************************************************/

#ifndef _HEAD_H
#define _HEAD_H

//head of sys
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <time.h>
#include <ncurses.h>
#include <locale.h>
#include <sys/timerfd.h>
#include <stdint.h>

//head of usr
#include "./chat_ui.h"
#include "./color.h"
#include "./conf.h"
#include "./datatype.h"
#include "./ioctl.h"
#include "./log.h"
#include "./network.h"
#include "./retval.h"
#include "./send_chat.h"


#ifdef _D
    
#define DBG(fmt, args...) {\
    printf(fmt, ##args);\
}

#else 

#define DBG(fmt, args...) 

#endif 

//filename : common.h
#define DEFARG(name, default_value) ((#name[0]) ? (name + 0) : default_value)
extern WINDOW *message_sub;
#define Show_Message(arg0, arg1, arg2, arg3) show_message(DEFARG(arg0, message_sub), DEFARG(arg1, NULL), arg2, DEFARG(arg3, 0))



#endif
