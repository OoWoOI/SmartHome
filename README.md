# SmartHome项目设计文档

## 项目概述
> SmartHome智能家居模拟系统，是一个模拟用户管理智能家居设备的系统，用户可以远程连接服务器，通过发送指令信息，实现了对智能家居设备状态信息管理。

## 系统架构
> SmartHome智能家居模拟系统，采用C/S架构，分为客户端和服务端。

- 客户端：在终端实现用户界面，允许用户与智能家居设备进行交互和控制
- 服务端：处理用户请求与管理智能家居设备的状态、信息。

## 技术选型

- 编程语言：C/C++、makefile
- 客户端界面：终端编程（ncurse库）
- 服务端：socket套接字、epoll（主从反应堆模式）
- 数据库：MySQL


## 功能设计

- 客户端：
  - 响应来自服务端的心跳信息;
  - 允许用户登录(userid + password)、下线（ctrl + c 信号处理机制）
  - 允许用户管理修改设备状态信息;
    
- 服务端：
  - 处理用户请求，包括连接请求、注销、设备控制等;
  - 定时发送心跳信息到客户端;
  - 与数据库交互，保存用户信息和设备状态信息;
  
## 接口设计
> SmartHome智能家居模拟系统中的接口设计，包含函数功能、函数原型、参数说明、返回值说明;

### 网络连接

 （1） `socket_create()` 函数:
  - 函数原型：
    ```C
    int socket_create(const int port);// 创建socket套接字，并绑定端口注册监听事件
    ```
  - 参数说明
    - `port`：指定端口；
  - 返回值：创建成功返回`sockfd`，失败返回`-1`;
  
  （2）`socket_connect()` 函数：
  - 函数原型：
     ```C
    int socket_connect(const char *ip, const int port);//远程连接服务器
     ```
  - 参数说明：
    - `ip`：远程连接服务器的IP地址
    - `port`：服务器连接端口
  - 返回值：连接成功返回新的`sockfd`, 连接失败返回`-1`;
    
### 日志系统
（1）`log_event()`函数：
 - 函数原型：
   ```C
     int log_event(const char *logfile, const int level, const char *msg);//向日志文件中打印日志信息
   ```
 - 参数说明：
   - `logfile`：日志文件的路径
   - `level`：日志事件的等级，分为普通（`LOG_EVENT_NORMAL`）、警告（`LOG_EVENT_WARNING`）、错误（`LOG_EVENT_ERROR`）;
   - `msg`：详细的日志信息描述
     
 - 返回值：成功返回`0`,失败返回`-1`;

### 配置文件
（1）`get_conf_val()`函数：
  - 函数原型：
    ```C
      int get_conf_val(const char *filepath, const char *key, char *val);//根据key获取val;
    ```
  - 参数说明：
    - `filepath`：配置文件
    - `key`：key值
    - `val`：传出参数，获得的val值
  
  - 返回值：成功返回`0`, 并且赋值`val`, 失败返回`-1`, `val`为NULL,
      
### 数据库


## 数据结构

## 测试计划

### 单元测试

### 集成测试

### 系统测试

### 性能测试


