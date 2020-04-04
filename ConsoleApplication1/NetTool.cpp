#include "stdafx.h"
#include "NetTool.h"

NetTool::NetTool(string & str, UInt &port)
	:_ipAddr(str),
	_port(port),
	_ccb(defaultNetToolConnectCallBack),
	_rcb(defaultNetToolReadCallBack),
	_wcb(defaultNetToolWriteCallBack),
	_ecb(defaultNetToolEventCallBack)
{
}

NetTool::~NetTool()
{
	clearBuffer();
	if (listener)
		evconnlistener_free(listener);
	if(base)
		event_base_free(base);
}

int NetTool::init()
{
	memset(&base, 0, sizeof(base));
	memset(&listener, 0, sizeof(listener));

	WSADATA wsa_data;
	WSAStartup(0x0201, &wsa_data);

	base = event_base_new();
	if (!base) {
		return 1;
	}

	Container *c = new Container();
	c->base = (event_base *)base;
	c->pointer = (void *)this;

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(_port);

	listener = evconnlistener_new_bind(base, NetTool::connectionCallBack, (void *)c,
		LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, -1,
		(struct sockaddr*)&addr,
		sizeof(addr));

	if (!listener) {
		return 1;
	}

	event_base_dispatch(base);

	return 0;
}

void NetTool::closeSocket(Fd fd)
{
	map<Fd, bufferevent *>::iterator it = m.find(fd);
	if (it != m.end() && it->second) {
		bufferevent_free(it->second);
		m.erase(fd);
	}
}

void NetTool::clearBuffer()
{
	map<Fd, bufferevent *>::iterator it = m.begin();
	for (; it != m.end(); ++it) {
		bufferevent_free(it->second);
	}
}

void NetTool::connectionCallBack(evconnlistener *, evutil_socket_t fd, sockaddr *, int socklen, void * user_data)
{
	//struct event_base *base = (struct event_base *)user_data;
	Container *c = (Container *)user_data;
	struct event_base *base = c->base;
	NetTool *nt = (NetTool *)c->pointer;

	struct bufferevent *bev;

	bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
	if (!bev) {
		return;
	}
	//insert into map,holder the bufferevent pointer
	nt->insertFd(fd, bev);
	//call back
	nt->_ccb(fd);

	bufferevent_setcb(bev, NetTool::readCallBack, NetTool::writeCallBack, NetTool::eventCallBack, (void *)nt);
	bufferevent_enable(bev, EV_WRITE | EV_READ);
}

void NetTool::readCallBack(bufferevent * bev, void * user_data)
{
	NetTool *nt = (NetTool *)user_data;

	intptr_t fd = bufferevent_getfd(bev);
	//cout << "fd:" << fd << endl;
	struct evbuffer *input = NULL;
	input = bufferevent_get_input(bev);
	size_t len;
	char *text;

	while (text = evbuffer_readln(input, &len, EVBUFFER_EOL_ANY)) {
		//cout << text << "\n" << endl;
		nt->_rcb(fd, (void *)text);
	}
}

void NetTool::writeCallBack(bufferevent * bev, void * user_data)
{
	NetTool *nt = (NetTool *)user_data;
	intptr_t fd = bufferevent_getfd(bev);
	nt->_wcb(fd);
}

void NetTool::eventCallBack(bufferevent * bev, short events, void * user_data)
{
	NetTool *nt = (NetTool *)user_data;
	intptr_t fd = bufferevent_getfd(bev);
	
	if (events & BEV_EVENT_EOF) {
		printf("Connection closed.\n");
		nt->_ecb(fd, (SocketStatus)BEV_EVENT_EOF);
	}
	else if (events & BEV_EVENT_ERROR) {
		printf("Got an error on the connection: %s\n",
			strerror(errno));/*XXX win32*/
	}
}

void defaultNetToolConnectCallBack(Fd fd) {
	printf("fd=%d\n", fd);
}

void defaultNetToolReadCallBack(Fd fd, void* data) {
	printf("read fd=%d,text=%s\n", fd, (char *)data);
}

void defaultNetToolWriteCallBack(Fd fd) {

}
void defaultNetToolEventCallBack(Fd fd, SocketStatus ss) {

}
