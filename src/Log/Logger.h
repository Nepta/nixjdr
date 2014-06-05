#ifndef LOGGER_H
#define LOGGER_H
#include "Network/Switch.h"
#include "Network/Receiver.h"

class Logger : public Switch, public Receiver{

public:
	Logger(QHash<QString, User *> *usersList);
	void insert(TargetCode targetCode, Receiver *receiver);

public slots:
	void processNewMessage(Header header, QByteArray &data);
};

#endif // LOGGER_H
