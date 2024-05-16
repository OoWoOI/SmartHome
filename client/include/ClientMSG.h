/*************************************************************************
	> File Name: ClientMSG.h
	> Author: 
	> Mail: 
	> Created Time: Thu 16 May 2024 04:13:23 PM CST
 ************************************************************************/

#ifndef _CLIENTMSG_H
#define _CLIENTMSG_H

#include "../common/include/DataTypes.h"


void *recv_MSG(void *arg);//接收消息
void *send_MSG(void *arg);//发送消息
void parse_MSG(struct SmhMsg *msg);//解析MSG
void encs_MSG(char *str, struct SmhMsg *msg);//封装MSG
void input_MSG(struct SmhMsg *msg);//输入
void output_MSG(struct SmhMsg *msg);//输出

#endif
