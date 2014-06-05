#ifndef LOGGER_H
#define LOGGER_H
#include "Network/Switch.h"
#include "Network/Receiver.h"
#include "Log.h"
#include <QStack>

class Logger : public Switch, public Receiver{

	QStack<Log*> logStack_;

public:
	Logger(QHash<QString, User *> *usersList);
	void insert(TargetCode targetCode, Receiver *receiver);
	Log* pop();
	void push(Log *log);

public slots:
	void processNewMessage(Header header, QByteArray &data);
};

#endif // LOGGER_H
