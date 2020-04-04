#pragma once

#ifndef _C_MESSAGE_INCLUDE_
#define _C_MESSAGE_INCLUDE_

enum MessageType {
	Receive,
	Send
};

typedef struct Message {
	MessageType type;
	void *data;
	Fd from;
	Fd to;
};

#endif // !_C_MESSAGE_INCLUDE_