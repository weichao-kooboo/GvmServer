#pragma once
#ifndef _C_NETTOOL_INCLUDE_
#define _C_NETTOOL_INCLUDE_

//libevent

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "getopt.h"
#ifndef _WIN32
#include <netinet/in.h>
# ifdef _XOPEN_SOURCE_EXTENDED
#  include <arpa/inet.h>
# endif
#include <sys/socket.h>
#endif

extern "C" {
#include "event2/event.h"
#include "event2/bufferevent.h"
#include "event2/buffer.h"
#include "event2/listener.h"
#include "event2/util.h"
}

#include <string>
using namespace std;
typedef uint32_t UInt;

#include "noncopyable.h"
#include "CALLBACK.h"
#include <map>

typedef struct Container{
	struct event_base *base;
	void *pointer;
};

//noncopyable
class NetTool:noncopyable
{
private:

public:
	NetTool() = delete;
	NetTool(string &str, UInt &port);
	~NetTool();
	int init();
	void setConnectCallBack(const ConnectCallBack &ccb) {
		_ccb = std::move(ccb);
	}
	void setReadCallBack(const ReadCallBack &rcb) {
		_rcb = std::move(rcb);
	}
	void setWriteCallBack(WriteCallBack wcb) {
		_wcb = std::move(wcb);
	}
	void setEventCallBack(const EventCallBack &ecb) {
		_ecb = std::move(ecb);
	}
	void closeSocket(Fd fd);
private:
	string _ipAddr;
	UInt _port;
	ConnectCallBack _ccb;
	ReadCallBack _rcb;
	WriteCallBack _wcb;
	EventCallBack _ecb;
	map<Fd, bufferevent *> m;
	void inline insertFd(Fd fd, bufferevent *bev) {
		m.insert(pair<Fd, bufferevent *>(fd, bev));
	}
	void clearBuffer();
	struct event_base *base;
	struct evconnlistener *listener;
	struct sockaddr_in addr;
	static void connectionCallBack(struct evconnlistener *, evutil_socket_t,
		struct sockaddr *, int socklen, void *);
	static void readCallBack(struct bufferevent *bev, void *user_data);
	static void writeCallBack(struct bufferevent *bev, void *user_data);
	static void eventCallBack(struct bufferevent *bev, short events, void *user_data);
};

#endif // !_C_NETTOOL_INCLUDE_


