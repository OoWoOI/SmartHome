/*************************************************************************
	> File Name: DataTypes.h
	> Author: 
	> Mail: 
	> Created Time: Wed 15 May 2024 08:28:45 AM CST
 ************************************************************************/

#ifndef _DATATYPES_H
#define _DATATYPES_H

enum device_type {
    DEVICE_LIGHT,
    DEVICE_SWITCH,
    DEVICE_THERMOSTAT,
    // 其他设备类型
};

// 设备状态枚举
enum device_state {
    DEVICE_STATE_OFF,
    DEVICE_STATE_ON,
    DEVICE_STATE_STANDBY,
    // 其他设备状态
};

// 设备结构体
struct device {
    int device_id;              // 设备ID
    char device_name[32];       // 设备名称
    enum device_type type;      // 设备类型
    enum device_state state;    // 设备状态
    // 其他设备属性
};



//登录相关的
struct  LogRequest {
    char name[20];
    char passwd[20];
    char msg[512];
};

struct LogResponse{
    int type; // 0 OK 1 NO
    char msg[512];
};
//登录期间交互
#define MAX_MSG 1024
//日常的消息交互，如聊天信息，统一为512长度

#define ACTION_GET_DEVICES 0x01
#define ACTION_UPDATE_DEVICE 0x02
#define ACTION_ADD_DEVICE 0x04
#define ACTION_DEL_DEVICE 0x08

//使用CTL报文对设备进行控制
struct Ctl {
    int action;
    //int device_id; 此处更新
    struct device dev;
};

#define SMH_HEART 0x01 //心跳
#define SMH_ACK 0x08 //ack
#define SMH_MSG 0x04 //聊天
#define SMH_WALL 0x02 //公告
#define SMH_CTL 0x10 //控制信息
#define SMH_FIN 0x100 //离场

struct SmhMsg{
    int type;  // type & SMH_HEART 验证是否为SMH_HEART信息
    int size;
    char name[20];
    char msg[MAX_MSG];
    struct Ctl ctl;
};

//新增了User结构体
struct User{
	char name[50];
};



#endif
