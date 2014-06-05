#ifndef MAPLOG_H
#define MAPLOG_H
#include "Log.h"
#include "Chat/Message.h"
#include "Database/DBComponent.h"

//TODO DBComponent <|-- MapLog : deficient by design
class MapLog : public Log, public DBComponent{
public:
	MapLog(Receiver& receiver);
	QString toString();
};

#endif // MAPLOG_H
