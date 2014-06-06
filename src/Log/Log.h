#ifndef LOG_H
#define LOG_H

#include "Network/Receiver.h"
#include "Network/Serializable/Message.h"
#include "Network/Header.h"
#include <QString>

class Log{
	Receiver& receiver_;
	Message message_;
	Header header_;

public:
	Log(Receiver& receiver);
	Receiver& reveiver();
	virtual QString toString() = 0;
	void setMessage(Message message);
	void setHeader(Header head);

protected:
	Message& getMessage();
	Header& getHeader();
};

#endif // LOG_H
