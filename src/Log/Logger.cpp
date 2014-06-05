#include "Logger.h"
#include <QDebug>
#include "Chat/Message.h"

Logger::Logger(QHash<QString, User *> *usersList) : Receiver(usersList){
}

void Logger::insert(TargetCode targetCode, Receiver *receiver){
	m_Nodes.insert(targetCode, receiver);
}

void Logger::processNewMessage(Header header, QByteArray &data){
	switchNewMessage(header, data);
	QString target(QString::number(header.getTarget()));
	QString code(QString::number(header.getCode()));
	Message message(data);
	qDebug() << "message captured: [" + target + "|" + code + "|" + message.getString() + "]";
}
