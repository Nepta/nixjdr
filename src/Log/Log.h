#ifndef LOG_H
#define LOG_H

#include "Network/Receiver.h"
#include "Chat/Message.h"
#include <QString>

class Log{
	Receiver& receiver_;
	Message message_;

public:
	Log(Receiver& receiver);
	Receiver& reveiver();
	virtual QString toString() = 0;
	virtual void setMessage(Message message);

protected:
	Message& getMessage();
};

#endif // LOG_H
