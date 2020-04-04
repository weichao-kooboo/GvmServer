#pragma once
#ifndef _C_CALLBACK_INCLUDE_

#include <functional>
using namespace std;

////typedef function<void(struct bufferevent *bev, void *user_data)> RDWR_CB;
////typedef function<void(struct bufferevent *bev, short events, void *user_data)> EVENT_CB;
//typedef void(*RDWR_CB)(struct bufferevent *bev, void *user_data);
//typedef void(*EVENT_CB)(struct bufferevent *bev, short events, void *user_data);
//typedef void(*LISTENER_CB)(struct evconnlistener *, evutil_socket_t,
//	struct sockaddr *, int socklen, void *);
//
//void defaultEventCB(struct bufferevent *bev, short events, void *user_data);
//void defaultConnectionCB(struct evconnlistener *, evutil_socket_t,
//	struct sockaddr *, int socklen, void *);

typedef intptr_t Fd;

enum SocketStatus
{

};

//??为啥不行
//函数指针无法在类中绑定类的成员函数
//setXXX会报错
//typedef void(*ConnectCallBack)(Fd fd);
//std::function可以绑定函数,函数指针,类非静态成员函数
//调用的时候使用const ConnectCallBack &表示传递的是函数指针
//使用std::bind绑定类的成员函数和类的指针,返回函数指针
//http://www.cplusplus.com/reference/functional/function/function/
//http://www.cplusplus.com/reference/functional/function/operator_func/
typedef std::function<void(Fd)> ConnectCallBack;
//typedef void(*ReadCallBack)(Fd fd, void* data);
typedef std::function<void(Fd fd, void* data)> ReadCallBack;
//typedef void(*WriteCallBack)(Fd fd);
typedef std::function<void(Fd fd)> WriteCallBack;
typedef std::function<void(Fd, SocketStatus)> EventCallBack;
//typedef void(*EventCallBack)(Fd fd, SocketStatus ss);

void defaultNetToolConnectCallBack(Fd fd);
void defaultNetToolReadCallBack(Fd fd, void* data);
void defaultNetToolWriteCallBack(Fd fd);
void defaultNetToolEventCallBack(Fd fd, SocketStatus ss);

#endif // !_C_CALLBACK_INCLUDE_
