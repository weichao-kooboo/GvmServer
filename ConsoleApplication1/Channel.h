#pragma once
#ifndef _C_CHANNEL_INCLUDE_
#define _C_CHANNEL_INCLUDE_
//������߼�һ��Ĳ���,���緢�ͽ��ܵ�
//ˮλ��С,��ӵ����,����channel����Ϣ֪ͨ
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

