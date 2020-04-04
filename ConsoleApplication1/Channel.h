#pragma once
#ifndef _C_CHANNEL_INCLUDE_
#define _C_CHANNEL_INCLUDE_
//定义更高级一点的操作,比如发送接受等
//水位大小,泵拥控制,其他channel的消息通知
#include "Socket.h"

class Channel
{
public:
	Channel() = delete;
	Channel(Fd &fd, weak_ptr<NetTool> nt);
	~Channel();
	Fd getFd() {
		return s->getFd();
	}
	void ReadCallBack(Fd fd, void *data);
	void WriteCallBack(Fd fd);
private:
	Socket *s;
	weak_ptr<NetTool> _nt;
};
#endif // !_C_CHANNEL_INCLUDE_

