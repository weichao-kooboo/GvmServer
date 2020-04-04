#pragma once

#ifndef _C_SERVER_INCLUDE_
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
#include <iostream>
#include "CALLBACK.h"
using namespace std;

class Server
{
public:
	Server();
	Server(string &str, int &&port);
	~Server();
	int run();
private:
	string _ipAddr;
	int _port;
	struct event_base *base;
	struct evconnlistener *listener;
	struct sockaddr_in addr;
	int checkInput(); 
	static void connectionCallBack(struct evconnlistener *, evutil_socket_t,
		struct sockaddr *, int socklen, void *);
	static void readCallBack(struct bufferevent *bev, void *user_data);
	static void writeCallBack(struct bufferevent *bev, void *user_data);
	static void eventCallBack(struct bufferevent *bev, short events, void *user_data);
};

#endif // !_C_SERVER_INCLUDE_

