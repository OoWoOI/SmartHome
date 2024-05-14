/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: Mon 13 May 2024 10:33:24 PM CST
 ************************************************************************/
 
#include "../include/Server.h"



SVR svr;//服务端实例

__attribute__((constructor)) 
void server_init() {
    DBG("Server Init.....\n");
    svr.port = GetPort(CONF_PATH);
    svr.conns = GetConns(CONF_PATH);
    return ;
}


static int add_epoll_event(int epoll_fd, struct epoll_event *event, int fd) {
    
    event->data.fd = fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, event) < 0) {
        close(fd);
        return -1;
    }

    return 0;
}

#define MAX_BUFFER_SIZE 1024

//处理客户端请求
int handleEvent(int fd) {
    //处理客户端的读事件

    // 处理连接事件
    char buffer[MAX_BUFFER_SIZE];
    ssize_t bytes = read(fd, buffer, MAX_BUFFER_SIZE);
    if (bytes > 0) {
        printf("Received message from client: %s\n", buffer);
        // 在这里可以进行具体的业务处理
    } else if (bytes == 0) {
        // 客户端关闭连接
        printf("Client closed connection\n");
        close(fd);
        return -1;
    } else {
        // 读取错误
        perror("Error reading from client");
        close(fd);
        return -1;
    }
    

    return 0;
}

int server_run() {
   
    if ((svr.sockfd = socket_create(svr.port)) < 0) {
        //创建sockfd实例失败
        PRINT(LOG_EVENT_ERROR, "创建SOCKET实例失败 ");
        return svr.sockfd;//返回错误码
    }
     
    //创建epoll实例
    int epoll_fd;
    
    if ((epoll_fd = epoll_create1(0)) < 0) {
        PRINT(LOG_EVENT_ERROR, "EPOLL实例创建失败");
        close(svr.sockfd);
        return epoll_fd;
    }
     
    //添加svr.sockfd到epoll实例中去
    struct epoll_event event;
    event.events = EPOLLIN;
    if (add_epoll_event(epoll_fd, &event, svr.sockfd) < 0) {
        PRINT(LOG_EVENT_ERROR, "添加sockfd到epoll实例中失败");
        close(epoll_fd);
        return -1;
    }
        
    struct epoll_event events[MAX_EVENTS];
    
    while (1) {
        int numEvents = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);

        if (numEvents < 0) {
            PRINT(LOG_EVENT_ERROR, "epoll_wait 出错了");
            break;
        }
        
        for (int i = 0; i < numEvents; i++) {
            if (events[i].data.fd == svr.sockfd) {//主反应堆，实现新的连接请求
                //处理连接请求
                int clnFd = accept(svr.sockfd, NULL, NULL);
                if (clnFd < 0) {
                    PRINT(LOG_EVENT_ERROR, "处理新客户端连接请求失败");
                    continue;
                }
                
                //设置客户端连接为非阻塞模式                
                if (make_nonblock(clnFd) < 0) {
                    PRINT(LOG_EVENT_ERROR, "设置clnFd为非阻塞模式失败");
                    close(clnFd);
                    continue;
                }
                //将客户端添加到epoll实例中去
                event.events = EPOLLIN | EPOLLET;//边缘触发模式
                if (add_epoll_event(epoll_fd, &event, clnFd) < 0) {
                    PRINT(LOG_EVENT_ERROR, "添加客户端soket到epoll实例中去失败");
                    continue;
                }
            } else {
                //从反应堆，处理客户端连接事件
                if (handleEvent(events[i].data.fd)  < 0) {
                    //需要移除epoll实例中的监听事件
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, events[i].data.fd, NULL);//
                    continue;
                }
            }
        }

    }
    
    //关闭套接字和epoll实例
    close(svr.sockfd);
    close(epoll_fd);
    return 0;
}
