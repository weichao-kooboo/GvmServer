#include "Socket.h"
#include "NetTool.h"


Socket::Socket(Fd &fd, weak_ptr<NetTool> nt)
	:_fd(fd)
	, _nt(nt)
{

}


Socket::~Socket()
{
	shared_ptr<NetTool> snt(_nt.lock());
	if (snt) {
		snt->closeSocket(_fd);
		printf("delete fd=%d", _fd);
	}
}
