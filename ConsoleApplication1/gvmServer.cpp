#include "stdafx.h"
#include "gvmServer.h"

#include <functional>


gvmServer::gvmServer(string &ipAddr,UInt &&port)
	:nt(new NetTool(ipAddr, port))
{
	nt->setConnectCallBack(std::bind(&gvmServer::ConnectCallBack, this, std::placeholders::_1));
	nt->setEventCallBack(std::bind(&gvmServer::EventCallBack, this, std::placeholders::_1, std::placeholders::_2));
	nt->setReadCallBack(std::bind(&gvmServer::ReadCallBack, this, std::placeholders::_1, std::placeholders::_2));
	nt->setWriteCallBack(std::bind(&gvmServer::WriteCallBack, this, std::placeholders::_1));
	nt->init();
}


gvmServer::~gvmServer()
{
}

void gvmServer::init()
{
	//nt(string("192.168.0.104"), 9992);
	//??为啥不行
	//nt->setConnectCallBack(this->ConnectCallBack);

	//run a thread
#ifdef _WIN32
	HANDLE hThread;
	DWORD threadId;
	hThread = CreateThread(NULL, 0, gvmServer::ThreadFunc, this, 0, &threadId);
#endif // WIN32
}

void gvmServer::ConnectCallBack(Fd fd)
{
	vec.push_back(new Channel(fd, weak_ptr<NetTool>(nt)));
	printf("client fd=%d\n", fd);
}

void gvmServer::EventCallBack(Fd fd, SocketStatus ss)
{
	vector<Channel*>::const_iterator it = vec.begin();
	for (; it != vec.end(); ++it) {
		if ((*it)->getFd() == fd) {
			break;
		}
	}
	if (it != vec.end()){
		delete (*it);
		vec.erase(it);
	}
}

void gvmServer::ReadCallBack(Fd fd, void * data)
{
	//收到消息后直接把消息放在队列中
	//然后消息发送给每个channel
	Message *msg = new Message();
	msg->type = MessageType::Receive;
	msg->data = data;
	msg->from = fd;
	msg_queue.push(msg);
}

void gvmServer::WriteCallBack(Fd fd)
{
}

Channel * gvmServer::findChannel(Fd fd)
{
	Channel *ch = NULL;
	vector<Channel*>::const_iterator it = vec.begin();
	for (; it != vec.end(); ++it) {
		if ((*it)->getFd() == fd) {
			break;
		}
	}
	
	if (it != vec.end()) {
		//delete (*it);
		//vec.erase(it);
		ch = std::move(*it);
	}
	return ch;
}

DWORD __stdcall gvmServer::ThreadFunc(LPVOID p)
{
	gvmServer *local_gvm = (gvmServer *)p;
	local_gvm->runQueue();
	return 0;
}

void gvmServer::runQueue()
{
	while (workType) {
		if (msg_queue.size() == 0)
			continue;
		Message *msg = msg_queue.front();
		msg_queue.pop();
		Channel *ch = findChannel(msg->from);
		ch->ReadCallBack(msg->from, msg->data);
		Sleep(100);
	}
}
