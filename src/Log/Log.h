#ifndef LOG_H
#define LOG_H

#include "Network/Receiver.h"
#include <QString>

class Log{

	Receiver& receiver_;

public:
	Log(Receiver& receiver);
	virtual QString toString() = 0;
	Receiver& reveiver();
};

#endif // LOG_H
