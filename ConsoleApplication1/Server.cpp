#include "Server.h"

string default_ip_addr = "127.0.0.1";

Server::Server()
	:Server(default_ip_addr, 8001)
{
	
}

Server::Server(string & str, int && port)
	:_ipAddr(str),
	_port(port)
{
}


Server::~Server()
{
}

int Server::run()
{
	if (checkInput()) {
		return 1;
	}

	memset(&base, 0, sizeof(base));
	memset(&listener, 0, sizeof(listener));

	WSADATA wsa_data;
	WSAStartup(0x0201, &wsa_data);

	base = event_base_new();
	if (!base) {
		return 1;
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(_port);

	listener = evconnlistener_new_bind(base, Server::connectionCallBack, (void *)base,
		LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, -1,
		(struct sockaddr*)&addr,
		sizeof(addr));

	if (!listener) {
		return 1;
	}

	event_base_dispatch(base);

	return 0;
}

int Server::checkInput()
{
	if (_ipAddr.length() == 0 || _port <= 0) {
		return 1;
	}
	//todo
	//check ip address
	return 0;
}

void Server::connectionCallBack(evconnlistener *, evutil_socket_t fd, sockaddr *, int socklen, void *user_data)
{
	struct event_base *base = (struct event_base *)user_data;
	struct bufferevent *bev;

	bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
	if (!bev) {
		return;
	}

	bufferevent_setcb(bev, readCallBack, Server::writeCallBack, Server::eventCallBack, NULL);
	bufferevent_enable(bev, EV_WRITE | EV_READ);
}

void Server::readCallBack(bufferevent * bev, void * user_data)
{
	intptr_t fd = bufferevent_getfd(bev);
	cout << "fd:" << fd << endl;
	struct evbuffer *input = NULL;
	input = bufferevent_get_input(bev);
	size_t len;
	char *text;
	
	while (text = evbuffer_readln(input, &len, EVBUFFER_EOL_ANY)) {
		cout << text << "\n" << endl;
	}
}

void Server::writeCallBack(bufferevent * bev, void * user_data)
{
	struct evbuffer *output;
	output = bufferevent_get_output(bev);
	if (evbuffer_get_length(output) == 0) {
		printf("flushed answer\n");
		//bufferevent_free(bev);
	}
}

void Server::eventCallBack(bufferevent * bev, short events, void * user_data)
{

}
