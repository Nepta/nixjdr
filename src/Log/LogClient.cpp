#include "LogClient.h"
#include "Network/Serializable/Message.h"

LogClient::LogClient(User *user, QHash<QString, User *> *usersList, Logger& logger) :
	SenderClient(user,usersList), logger_(*logger.getGui()){
}

void LogClient::processNewData(Header header, QByteArray &data){
	Message message(data);
	QString log = message.getString();
	logger_.pushLog(log);
}

void LogClient::sendMessageToServer(QString msg){
	sendMessageToServer(msg, 0);
}

void LogClient::sendMessageToServer(const QString &msg, quint16 code){
	Message message(msg);
	TargetCode target = TargetCode::LOGGER_SERVER;
	sendPacketToServer(code, (quint16)target, message);
}