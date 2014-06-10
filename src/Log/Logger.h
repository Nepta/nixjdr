#ifndef LOGGER_H
#define LOGGER_H
#include "Network/Switch.h"
#include "Network/Receiver.h"
#include "Database/Database.h"
#include "Log.h"
#include "LogGui.h"
#include <QStack>

class Logger : public Switch, public Receiver {

	QStack<Log*> logStack_;
	LogGui *gui_;

public:
	void setGui(LogGui *gui);
	void insertRoute(TargetCode targetCode, Receiver *receiver);
	Log* pop();
	void push(Log *log);

public slots:
	void processNewData(Header header, QByteArray &data);
};

#endif // LOGGER_H
