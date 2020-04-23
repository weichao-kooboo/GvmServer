// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include <string>
#include <iostream>

#include "Server.h"
#include "NetTool.h"
#include "gvmServer.h"
using namespace std;

#include "RegisterCenter.h"


#include <WinSock2.h>
#include <Windows.h>

//1.输入字符串的解析
//2.信号处理
//3.添加网络库

int getInput(string &str);
void listener_cb(struct evconnlistener *listener, evutil_socket_t fd,
	struct sockaddr *sa, int socklen, void *user_data);
void conn_readcb(struct bufferevent *bev, void *user_data);
void conn_writecb(struct bufferevent *bev, void *user_data);
void conn_eventcb(struct bufferevent *bev, short events, void *user_data);
void signal_cb(evutil_socket_t sig, short events, void *user_data);
static void operation_buffer();

int main() {
	//Server s(string("192.168.2.2"),9992);
	//s.run();
	//operation_buffer();
	//NetTool t(string("192.168.0.104"), 9992);
	//t.init();
	gvmServer gvm(string("192.168.0.104"), 9992);
	//gvm.init();

	tool::RegisterCenter<int>::CreateInstance();
	int x;
	cin >> x;
}

int h()
{
	string account;
	string password;

	setbuf(stdout, NULL);
	setbuf(stderr, NULL);

	if ((getInput(account) || getInput(password)) != 0) {
		return 1;
	}

	struct event_base *base;
	struct evconnlistener *listener;
	struct event *signal_event;

	struct sockaddr_in addr;

	WSADATA wsa_data;
	WSAStartup(0x0201, &wsa_data);

	base = event_base_new();
	if (!base) {
		return 1;
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9910);

	listener=evconnlistener_new_bind(base, listener_cb, (void *)base,
		LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, -1,
		(struct sockaddr*)&addr,
		sizeof(addr));

	if (!listener) {
		return 1;
	}

	signal_event = evsignal_new(base, SIGINT, signal_cb, (void*)base);

	if (!signal_event || event_add(signal_event, NULL) < 0) {
		return 1;
	}

	event_base_dispatch(base);

	cout << account << ' ' << password << endl;
end:

    return 0;
}

int getInput(string & str)
{
	char a;
	while ((a = cin.get()) != 10) {
		if (a < 48 || a>57) {
			cout << "不能输入除数字以外的字符" << endl;
			return 1;
		}
		str.push_back(a);
	}
	return 0;
}

void listener_cb(evconnlistener * listener, evutil_socket_t fd, sockaddr * sa, int socklen, void * user_data)
{
	struct event_base *base = (struct event_base *)user_data;
	struct bufferevent *bev;

	bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
	if (!bev) {
		return;
	}
	bufferevent_setcb(bev, conn_readcb, conn_writecb, conn_eventcb, NULL);
	bufferevent_enable(bev, EV_WRITE | EV_READ);
}

void conn_readcb(bufferevent * bev, void * user_data)
{
}

void conn_writecb(bufferevent * bev, void * user_data)
{
}

void conn_eventcb(bufferevent * bev, short events, void * user_data)
{
}

void signal_cb(evutil_socket_t sig, short events, void *user_data){

}


static void
fifo_read(evutil_socket_t fd, short event, void *arg) {
	int k = 0;
}

static void operation_buffer() {
	struct event *evfifo;
	struct event_base *base;

	WSADATA wsa_data;
	WSAStartup(0x0201, &wsa_data);

	HANDLE socket;
	//open a file
	socket = CreateFileA("C:\\Users\\lihongxing\\test.txt",
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (socket == INVALID_HANDLE_VALUE) {
		printf("open error %d\n", GetLastError());
		return;
	}
	evbuffer *evbuf = evbuffer_new();
	int length = evbuffer_add_file(evbuf, (evutil_socket_t)socket, 0, -1);
	if (length != 0) {

	}
	/*base = event_base_new();
	evfifo = event_new(base, (evutil_socket_t)socket, EV_READ | EV_PERSIST, fifo_read,
		event_self_cbarg());
	event_add(evfifo, NULL);

	event_base_dispatch(base);*/
}
