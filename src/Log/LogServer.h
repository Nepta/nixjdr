#ifndef LOGSERVER_H
#define LOGSERVER_H

#include "Network/SenderServer.h"
#include "Network/Receiver.h"

class LogServer : public SenderServer, public Receiver{
	Q_OBJECT

public:
	LogServer(QHash<QString, User *> *usersList);
	void processNewData(Header header, QByteArray &data);
};

#endif // LOGSERVER_H
