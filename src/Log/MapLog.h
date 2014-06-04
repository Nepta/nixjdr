#ifndef MAPLOG_H
#define MAPLOG_H
#include "Log.h"
#include "Chat/Message.h"

class MapLog : public Log{
public:
	MapLog(Receiver& receiver);
	QString toString();
};

#endif // MAPLOG_H
