#include "LogClient.h"
#include "Network/Serializable/Message.h"

void LogClient::processNewData(Header header, QByteArray &data){
	Message message(data);
	QString log = message.getString();
	logGui_.pushLog(log);
}
