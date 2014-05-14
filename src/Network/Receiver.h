#ifndef RECEIVER_H
#define RECEIVER_H

#include <QString>
#include "../chat/ChatHeader.h"

class Receiver{
public:
	Receiver();
	void processNewMessage(ChatHeader header, QString message) = 0;
};

#endif // RECEIVER_H
