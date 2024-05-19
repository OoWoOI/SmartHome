/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: Fri 17 May 2024 08:37:35 PM CST
 ************************************************************************/

#include "../include/server.h"

void main_reactor_init(MainReactor *main_reactor) {
    main_reactor->epoll_fd = epoll_create1(0);
    if (main_reactor->epoll_fd == -1) {
        PRINT(LOG_LEVEL_ERROR, "epoll_create1 main_reactor");
        exit(EXIT_FAILURE);
    }

    main_reactor->timer_fd = timerfd_create(CLOCK_REALTIME, 0);
    if (main_reactor->timer_fd == -1) {
        PRINT(LOG_LEVEL_ERROR, "timerfd_create error");
        exit(EXIT_FAILURE);
    }

    struct itimerspec new_value;
    new_value.it_value.tv_sec = HEARTBEAT_INTERVAL;
    new_value.it_value.tv_nsec = 0;
    new_value.it_interval.tv_sec = HEARTBEAT_INTERVAL;
    new_value.it_interval.tv_nsec = 0;

    if (timerfd_settime(main_reactor->timer_fd, 0, &new_value, NULL) == -1) {
        PRINT(LOG_LEVEL_ERROR, "timerfd_settime error");
        exit(EXIT_FAILURE);
    }

    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = main_reactor->timer_fd;

    if (epoll_ctl(main_reactor->epoll_fd, EPOLL_CTL_ADD, main_reactor->timer_fd, &ev) == -1) {
        PRINT(LOG_LEVEL_ERROR, "epoll_ctl error");
        exit(EXIT_FAILURE);
    }

    main_reactor->sub_reactor.epoll_fd = epoll_create1(0);
    if (main_reactor->sub_reactor.epoll_fd == -1) {
        PRINT(LOG_LEVEL_ERROR, "epoll_create1 sub_reactor error");
        exit(EXIT_FAILURE);
    }
    main_reactor->sub_reactor.client_count = 0;
    pthread_mutex_init(&main_reactor->sub_reactor.client_mutex, NULL);
}

void main_reactor_run(MainReactor *main_reactor, int listen_fd) {
    struct epoll_event events[MAX_EVENTS];
    while (1) {
        int nfds = epoll_wait(main_reactor->epoll_fd, events, MAX_EVENTS, -1);
        if (nfds == -1) {
            PRINT(LOG_LEVEL_ERROR, "epoll_wait main_reactor events error");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < nfds; ++i) {
            if (events[i].data.fd == listen_fd) {
                handle_new_connection(main_reactor, listen_fd);
            } else if (events[i].data.fd == main_reactor->timer_fd) {
                // 定时器事件交给心跳线程处理
            }
        }
    }
}

void handle_new_connection(MainReactor *main_reactor, int listen_fd) {
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int client_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_fd == -1) {
        PRINT(LOG_LEVEL_ERROR, "accept new connections error");
        return;
    }

    SubReactor *sub_reactor = &main_reactor->sub_reactor;
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = client_fd;

    if (epoll_ctl(sub_reactor->epoll_fd, EPOLL_CTL_ADD, client_fd, &ev) == -1) {
        PRINT(LOG_LEVEL_ERROR, "epoll_ctl add error");
        close(client_fd);
        return;
    }

    pthread_mutex_lock(&sub_reactor->client_mutex);
    if (sub_reactor->client_count < MAX_CLIENTS) {
        sub_reactor->clients[sub_reactor->client_count++] = client_fd;
    } else {
        PRINT(LOG_LEVEL_ERROR, "Max clients reached, cannot accept more connections");
        close(client_fd);
    }
    pthread_mutex_unlock(&sub_reactor->client_mutex);
}

void *heartbeat_thread(void *arg) {
    MainReactor *main_reactor = (MainReactor *)arg;
    while (1) {
        uint64_t expirations;
        ssize_t s = read(main_reactor->timer_fd, &expirations, sizeof(expirations));
        if (s != sizeof(expirations)) {
            PRINT(LOG_LEVEL_ERROR, "read error heartbeat");
            exit(EXIT_FAILURE);
        }

        SubReactor *sub_reactor = &main_reactor->sub_reactor;
        pthread_mutex_lock(&sub_reactor->client_mutex);
        for (int i = 0; i < sub_reactor->client_count; ++i) {
            int client_fd = sub_reactor->clients[i];
            const char *heartbeat_msg = "HEARTBEAT\n";
            //TODO : 发送到客户端的心跳信息
            if (send(client_fd, heartbeat_msg, strlen(heartbeat_msg), 0) == -1) {
                PRINT(LOG_LEVEL_ERROR, "Send HeartBeat Error");
                close(client_fd);
                sub_reactor->clients[i] = sub_reactor->clients[--sub_reactor->client_count];
                --i;
            }
        }
        pthread_mutex_unlock(&sub_reactor->client_mutex);
    }
}

void sub_reactor_run(SubReactor *sub_reactor) {
    struct epoll_event events[MAX_EVENTS];
    while (1) {
        int nfds = epoll_wait(sub_reactor->epoll_fd, events, MAX_EVENTS, -1);
        if (nfds == -1) {
            PRINT(LOG_LEVEL_ERROR, "客户端连接中断!");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < nfds; ++i) {
            handle_client_event(events[i].data.fd);
        }
    }
}


void get_client_info(int client_fd, char *client_ip, int *client_port) {
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(struct sockaddr_in);
    if (getpeername(client_fd, (struct sockaddr *)&client_addr, &addr_len) == -1) {
        PRINT(LOG_LEVEL_ERROR, "getpeername 失败");
        return ;
    }
    inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
    *client_port = ntohs(client_addr.sin_port);
    return ;
}

void handle_client_event(int client_fd) {
    //获取客户端信息 
    char client_ip[INET_ADDRSTRLEN] = {0};
    int client_port = 0;
    get_client_info(client_fd, client_ip, &client_port);
    char buffer[1024];

    int n = read(client_fd, buffer, sizeof(buffer) - 1);
    if (n <= 0) {
        if (n == 0) {
            char buff[1024] = {0};
            sprintf(buff, "Client %s : %d disconnected", client_ip, client_port);
            PRINT(LOG_LEVEL_NORMAL, buffer);
        } else {
            PRINT(LOG_LEVEL_ERROR, "read info from client error");
        }
        close(client_fd);
        return;
    }
    //TODO : 打印消息
    buffer[n] = '\0';
    printf("Received message from %s : %d >>  %s\n", client_ip, client_port, buffer);
    write(client_fd, buffer, n);
}

void add_one_epoll(int epoll_fd, int fd){
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = fd;

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ev) == -1) {
        PRINT(LOG_LEVEL_ERROR, "epoll_ctl");
        close(fd);
        exit(EXIT_FAILURE);
    }
    return ;
}

int server_run() {
    int port = getSvrPort();
    int listen_fd;
    if ((listen_fd = socket_create(port)) < 0) {
        PRINT(LOG_LEVEL_ERROR, "创建listen_fd失败");
        exit(EXIT_FAILURE);
    }

    MainReactor main_reactor;
    main_reactor_init(&main_reactor);
    
    add_one_epoll(main_reactor.epoll_fd, listen_fd);
    
    if (pthread_create(&main_reactor.sub_reactor.heartbeat_thread, NULL, heartbeat_thread, (void *)&main_reactor) != 0) {
        PRINT(LOG_LEVEL_ERROR, "pthread_create");
        close(listen_fd);
        exit(EXIT_FAILURE);
    }

    pthread_t sub_reactor_thread;
    if (pthread_create(&sub_reactor_thread, NULL, (void *(*)(void *))sub_reactor_run, (void *)&main_reactor.sub_reactor) != 0) {
        PRINT(LOG_LEVEL_ERROR, "pthread_create");
        close(listen_fd);
        exit(EXIT_FAILURE);
    }

    main_reactor_run(&main_reactor, listen_fd);

    pthread_join(main_reactor.sub_reactor.heartbeat_thread, NULL);
    pthread_join(sub_reactor_thread, NULL);

    close(listen_fd);
    return 0;
}
