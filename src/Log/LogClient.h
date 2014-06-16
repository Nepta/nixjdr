#ifndef LOGCLIENT_H
#define LOGCLIENT_H

#include "Network/SenderClient.h"
#include "Network/Receiver.h"
#include "Log/Logger.h"
#include "Log/LogGui.h"

class LogClient : public SenderClient, public Receiver{
	Q_OBJECT

	LogGui& logger_;

public:
	LogClient(User *user, QHash<QString, User *> *usersList, Logger& logger);
	void processNewData(Header header, QByteArray &data);

public slots:
	void sendMessageToServer(const QString &msg, quint16 code);
};

#endif // LOGCLIENT_H
