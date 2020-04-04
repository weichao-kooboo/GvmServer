#include "Channel.h"


Channel::Channel(Fd &fd, weak_ptr<NetTool> nt)
	:_nt(nt),
	s(new Socket(fd, nt))
{

}

Channel::~Channel()
{
	delete s;
}


void Channel::ReadCallBack(Fd fd, void * data)
{
}

void Channel::WriteCallBack(Fd fd)
{
}
