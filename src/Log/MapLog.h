#ifndef MAPLOG_H
#define MAPLOG_H
#include "Log.h"
#include "Network/Serializable/Message.h"

class MapLog : public Log {
public:
	MapLog(Receiver& receiver);
	QString toString();
};

#endif // MAPLOG_H
