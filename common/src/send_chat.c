/*************************************************************************
	> File Name: SendChat.c
	> Author: 
	> Mail: 
	> Created Time: Fri 17 May 2024 03:53:52 PM CST
 ************************************************************************/

#include "../include/head.h"

extern WINDOW *input_sub, *input_win;

void send_chat(int sockfd, struct SmhMsg *chat_msg) {
    echo();
    nocbreak();
    bzero(chat_msg->msg, sizeof(chat_msg->msg));
    chat_msg->type = SMH_WALL;
    curs_set(1);
    w_gotoxy_puts(input_win, 1, 1, "Input Message : ");
    mvwscanw(input_win, 2, 10, "%[^\\n]s", chat_msg->msg);
    //TODO 判断如果读入的信息非空，则发送到服务端
    wclear(input_win);
    curs_set(0);
    box(input_win, 0, 0);
    wrefresh(input_win);
    noecho();
    cbreak();

}

