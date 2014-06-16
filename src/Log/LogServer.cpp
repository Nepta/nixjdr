#include "LogServer.h"
#include "Network/Switch.h"
#include "Network/Serializable/Message.h"

LogServer::LogServer(QHash<QString, User *> *usersList) : SenderServer(usersList){
}

void LogServer::processNewData(Header header, QByteArray &data)
{
	Message message(data);
	quint16 targetCode((quint16)TargetCode::LOGGER_CLIENT);
	QList<User*> recipients = m_UsersList->values();
	sendPacketToList(targetCode, header.getCode(), message, recipients);
}
