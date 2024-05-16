/*************************************************************************
	> File Name: ClientMSG.c
	> Author: 
	> Mail: 
	> Created Time: Thu 16 May 2024 04:12:46 PM CST
 ************************************************************************/

#include "../include/Client.h"
#include "../include/ClientMSG.h"

extern struct Client_Info cln;

//从服务器接收数据
void *recv_MSG(void *arg) {
    while (1) {
        struct SmhMsg msg;
        memset(&msg, 0, sizeof(msg));//初始化内存
        //接收消息
        ssize_t rsize = recv(cln.sockfd, &msg, sizeof(msg), 0);

        if (rsize == -1) {
            //服务器出现问题
            close(cln.sockfd);
            exit(EXIT_FAILURE);
        } else if (rsize == 0) {
            //服务器关闭连接
            close(cln.sockfd);
            exit(EXIT_SUCCESS);
        }
        output_MSG(&msg);//输出消息
    }

    return NULL;
}

//向服务器发送消息
void *send_MSG(void *arg) {
    struct SmhMsg msg;
    while (1) {
        memset(&msg, 0, sizeof(msg));
        input_MSG(&msg);//输入并打包数据 
        ssize_t wsize = send(cln.sockfd, &msg, sizeof(msg), 0);//发送数据
        if (wsize == -1) {
          //发送消息失败  
          close(cln.sockfd);
          exit(EXIT_FAILURE);
        } else if (wsize == 0) {
          //服务器关闭连接
          close(cln.sockfd);
          exit(EXIT_SUCCESS);
        } 
        //发送成功
    }

    return NULL;
}


//解析消息
void parse_MSG(struct SmhMsg *msg) {
    if (msg == NULL ) return ;

    if (msg->type & SMH_HEART) {
        //心跳信息
        
    } else if (msg->type & SMH_WALL) {
        //公告信息

    } else if (msg->type & SMH_MSG) {
        //私聊信息

    } else if (msg->type & SMH_FIN) {
        //离场信息
        
    } else {
        //不支持消息类型

    }
    
    return ;
}

//静态方法只在本文件使用
static void parse_ctl(char *str, struct Ctl *ctl) {
    char *instruction = strtok(str, " ");
    if (instruction == NULL) {
        ctl->action = -1;
        return ;
    }
    if (strcmp(instruction, "#1") == 0) {
        ctl->action = ACTION_GET_DEVICES;//查看可用设备
    } else if (strcmp(instruction, "#21") == 0) {
        ctl->action = ACTION_UPDATE_DEVICE;//修改设备状态
        char *dev_id_str = strtok(NULL, " ");
        if (dev_id_str == NULL) {
            ctl->action = -1;
            return ;
        }
        ctl->dev.device_id = atoi(dev_id_str);
        ctl->dev.state = DEVICE_STATE_ON;//修改设备为开
    } else if (strcmp(instruction, "#22") == 0) {
        ctl->action = ACTION_UPDATE_DEVICE;//修改设备状态
        char *dev_id_str = strtok(NULL, " ");
        if (dev_id_str == NULL) {
            ctl->action = -1;
            return ;
        }
        ctl->dev.device_id = atoi(dev_id_str);
        ctl->dev.state = DEVICE_STATE_OFF;//修改设备状态为关
    } else if (strcmp(instruction, "#23") == 0) {
        ctl->action = ACTION_UPDATE_DEVICE;//修改设备状态
        char *dev_id_str = strtok(NULL, " ");
        if (dev_id_str == NULL) {
            ctl->action = -1;
            return ;
        }
        ctl->dev.device_id = atoi(dev_id_str);
        ctl->dev.state = DEVICE_STATE_STANDBY;//修改设备状态为待机
    } else if (strcmp(instruction, "#31") == 0) {
        ctl->action = ACTION_ADD_DEVICE;//添加设备
        ctl->dev.type = DEVICE_LIGHT;//设备类型为灯
        char *dev_name = strtok(NULL, " ");
        if (dev_name == NULL) {
            ctl->action = -1;
            return ;
        }
        strncpy(ctl->dev.device_name, dev_name, sizeof(ctl->dev.device_name) - 1);
    } else if (strcmp(instruction, "#32") == 0) {
        ctl->action = ACTION_ADD_DEVICE;//添加设备
        ctl->dev.type = DEVICE_SWITCH;//设备类型为开关
        char *dev_name = strtok(NULL, " ");
        if (dev_name == NULL) {
            ctl->action = -1;
            return ;
        }
        strncpy(ctl->dev.device_name, dev_name, sizeof(ctl->dev.device_name) - 1);
    } else if (strcmp(instruction, "#33") == 0) {
        ctl->action = ACTION_ADD_DEVICE;//添加设备
        ctl->dev.type = DEVICE_THERMOSTAT;//设备类型为恒温设备
        char *dev_name = strtok(NULL, " ");
        if (dev_name == NULL) {
            ctl->action = -1;
            return ;
        }
        strncpy(ctl->dev.device_name, dev_name, sizeof(ctl->dev.device_name) - 1);
    } else if (strcmp(instruction, "#4") == 0) {
        ctl->action = ACTION_DEL_DEVICE;//删除设备
        char *dev_id_str = strtok(NULL, " ");
        if (dev_id_str == NULL) {
            ctl->action = -1;
            return ;
        }
        ctl->dev.device_id = atoi(dev_id_str);
    } else {
        ctl->action = -1;
    }

    return ;
}


static int isWALL(char *str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] == '@') {
            return 0;//私聊
        }
    }
    return 1;
}

//封装消息
void encs_MSG(char *str, struct SmhMsg *msg) {
    
    //解析字符串,如果str[0] == '#', 说明是设备控制符
    if (msg == NULL || strlen(str) == 0) return ;
    
    if (str[0] == '#') {//控制信息
        msg->type = SMH_CTL;
        parse_ctl(str, &(msg->ctl));
        return ;
    } 
    
    //公告
    if (isWALL(str)) {
        msg->type = SMH_WALL;
        strcpy(msg->msg, str);
    } else {
        msg->type = SMH_MSG;//私聊
        int ind = -1;
        for (int i = 0; str[i]; i++) {
            if (str[i] == '@') ind = i; 
        }
        strcpy(msg->name, str + ind + 1);
        if (ind == 0) return ;
        strncpy(msg->msg, str, sizeof(char) * ind);
    }

    return ;
}


//输入消息
void input_MSG(struct SmhMsg *msg) {
    char buff[1024] = {0};
    printf("请输入 >> : ");
    scanf("%s", buff);
    encs_MSG(buff, msg);
    return ;
}


//输出消息
void output_MSG(struct SmhMsg *msg) {
    if (msg == NULL) return ;
    printf("收到来自服务器的消息 >> : \n");
    parse_MSG(msg);
    return ;
}

