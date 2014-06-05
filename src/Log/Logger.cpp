#include "Logger.h"
#include <QDebug>
#include "Chat/Message.h"
#include "MapLog.h"

Logger::Logger(QHash<QString, User *> *usersList) : Receiver(usersList){
}

void Logger::insert(TargetCode targetCode, Receiver *receiver){
	m_Nodes.insert(targetCode, receiver);
}

void Logger::processNewMessage(Header header, QByteArray &data){
	switchNewMessage(header, data);

	MapLog log(*this);
	log.setMessage(data);
	log.setHeader(header);
	qDebug() << log.toString();
}
