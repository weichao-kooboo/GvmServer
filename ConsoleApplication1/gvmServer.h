#pragma once
#ifndef _C_GVMSERVER_INCLUDE_
#define _C_GVMSERVER_INCLUDE_

#include "NetTool.h"
#include <vector>
#include <list>
#include <queue>
#include "Channel.h"
#include "Message.h"


class gvmServer
{
public:
	gvmServer() = delete;
	gvmServer(string &ipAddr, UInt &&port);
	~gvmServer();
	void init();
	void ConnectCallBack(Fd fd);
	void EventCallBack(Fd fd, SocketStatus ss);
	void ReadCallBack(Fd fd, void *data);
	void WriteCallBack(Fd fd);
private:
	shared_ptr<NetTool> nt;
	vector<Channel*> vec;
	//need a thread to deal with
	queue<Message*, list<Message*>> msg_queue;
	Channel *findChannel(Fd fd);
	bool workType = true;
	static DWORD WINAPI ThreadFunc(LPVOID);
	void runQueue();
};
#endif // !_C_GVMSERVER_INCLUDE_

