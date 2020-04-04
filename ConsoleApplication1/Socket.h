#pragma once

#ifndef _C_SOCKET_INCLUDE_
#define _C_SOCKET_INCLUDE_

#include "CALLBACK.h"
#include <memory>

class NetTool;

//设置所有描述符的操作
class Socket
{
public:
	Socket() = delete;
	Socket(Fd &fd,weak_ptr<NetTool> nt);
	Fd getFd() {
		return _fd;
	}
	~Socket();
private:
	Fd _fd;
	string _peerIp;
	weak_ptr<NetTool> _nt;
};
#endif // !_C_SOCKET_INCLUDE_

