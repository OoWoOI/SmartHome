/*************************************************************************
	> File Name: ClientUI.c
	> Author: 
	> Mail: 
	> Created Time: Thu 16 May 2024 08:08:11 PM CST
 ************************************************************************/

#include "../include/ClientUI.h"

extern WINDOW *message_win, *message_sub,  *info_win, *input_win, *info_sub;
extern int message_num;

WINDOW *create_newwin(int width, int heigth, int startx, int starty) {
    WINDOW *win;
    win = newwin(heigth, width, starty, startx);
    box(win, 0, 0);
    wrefresh(win);
    return win;
}

void destroy_win(WINDOW *win) {
    wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(win);
    delwin(win);
}

void gotoxy(int x, int y) {
    move(y, x);
}

void gotoxy_putc(int x, int y, int c) {
    move(y, x);
    addch(c);
    move(LINES - 1, 1);
    refresh();
}

void gotoxy_puts(int x, int y, char* s) {
    move(y, x);
    addstr(s);
    move(LINES - 1, 1);
    refresh();
}

void w_gotoxy_putc(WINDOW *win, int x, int y, int c) {
    mvwaddch(win, y, x, c);
    move(LINES - 1, 1);
    wrefresh(win);
}

void w_gotoxy_puts(WINDOW *win, int x, int y, char *s) {
    mvwprintw(win, y, x, s);
    move(LINES - 1, 1);
    wrefresh(win);
}

void show_info();

void init_ui() {
    initscr();
    clear();
    if (!has_colors() || start_color() == ERR) {
        endwin();
        fprintf(stderr, "终端不支持颜色!\\n");
        exit(1);
    }
    init_pair(1, COLOR_GREEN, COLOR_BLACK); //绿色
    init_pair(2, COLOR_RED, COLOR_BLACK);//红色
    init_pair(3, COLOR_WHITE, COLOR_BLACK);//白色
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);//黄色
    init_pair(5, COLOR_CYAN, COLOR_BLACK);//青色
    init_pair(6, COLOR_BLUE, COLOR_BLACK);//蓝色
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK); //洋红
    init_pair(8, COLOR_BLACK, COLOR_GREEN);
    init_pair(9, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(10, COLOR_BLACK, COLOR_RED);
    init_pair(11, COLOR_BLACK, COLOR_BLUE);
    init_pair(12, COLOR_BLACK, COLOR_YELLOW);

    message_win = create_newwin(MSG_WIDTH, MSG_HEIGHT, 2, 1);
    message_sub = subwin(message_win, MSG_HEIGHT - 2, MSG_WIDTH - 2, 2, 3);
    scrollok(message_sub, 1);
    info_win = create_newwin(INFO_WIDTH, MSG_HEIGHT, 2 + MSG_WIDTH, 1);
    //info_sub = subwin(info_win, MSG_HEIGHT - 2, MSG_WIDTH - 2, 4, MSG_WIDTH + 1);
    input_win = create_newwin(INFO_WIDTH + MSG_WIDTH, INPUT_HEIGHT, 2, MSG_HEIGHT + 1);
    //input_sub = subwin(input_win, MSG_HEIGHT + 1, MSG_WIDTH + INFO_WIDTH - 2, MSG_HEIGHT + 1, 4);

    wattron(message_win, COLOR_PAIR(1));
    box(message_win, 0, 0);
    wattron(input_win, COLOR_PAIR(1));
    box(input_win, 0, 0);
    wattron(info_win, COLOR_PAIR(1));
    box(info_win, 0, 0);

    show_info();
    wrefresh(message_win);
    wrefresh(info_win);
    wrefresh(input_win);
}

void show_info() {
    wattron(info_win, COLOR_PAIR(2));
    w_gotoxy_puts(info_win, MSG_WIDTH + 1, 2, "Help:");
    wattron(info_win, COLOR_PAIR(7));
    w_gotoxy_puts(info_win, 3, 3, "start with @user 私聊");
    wrefresh(info_win);
}


void show_message(WINDOW *win, struct User *user, char *msg, int type) {
    curs_set(0);
    time_t time_now = time(NULL);
    struct tm* tm = localtime(&time_now);
    char timestr[20] = {0};
    char username[80] = {0};
    sprintf(timestr, "%02d:%02d:%02d ", tm->tm_hour, tm->tm_min, tm->tm_sec);
    if (type) {
        wattron(win, COLOR_PAIR(4));
        strcpy(username, "Server Info : ");
    } else {
        wattron(win, COLOR_PAIR(6));
        if (!strlen(user->name)) {
            strcpy(username, "Server Info : ");
        } else {
            sprintf(username, "%s : ", user->name);
        }
    }

    if (strstr(username, "中心") != NULL)
        wattron(win, COLOR_PAIR(4));
    if (message_num <= MSG_HEIGHT - 3) {
        w_gotoxy_puts(win, 10, message_num, username);
        wattron(win, COLOR_PAIR(3));
        w_gotoxy_puts(win, 10 + strlen(username), message_num, msg);
        wattron(win, COLOR_PAIR(5));
        w_gotoxy_puts(win, 1, message_num, timestr);
    } else {
        message_num = MSG_HEIGHT - 3;
        scroll(win);
        w_gotoxy_puts(win, 10, message_num, username);
        wattron(win, COLOR_PAIR(3));
        w_gotoxy_puts(win, 10 + strlen(username), message_num, msg);
        wattron(win, COLOR_PAIR(5));
        w_gotoxy_puts(win, 1, message_num, timestr);

    }
    int linenum = ceil((12.0 + strlen(username) +strlen(msg)) / MSG_WIDTH);
    message_num += linenum;
    wrefresh(win);
    curs_set(0);
}

