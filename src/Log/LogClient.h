#ifndef LOGCLIENT_H
#define LOGCLIENT_H

#include "Network/SenderClient.h"
#include "Network/Receiver.h"
#include "Log/LogGui.h"

class LogClient : public SenderClient, public Receiver{
	Q_OBJECT

	LogGui& logger_;

public:
	LogClient(User *user, QHash<QString, User *> *usersList, LogGui& logger);
    void processNewData(Header, QByteArray &data);

public slots:
	void sendMessageToServer(QString msg);
	void sendMessageToServer(const QString &msg, quint16 code);
};

#endif // LOGCLIENT_H
