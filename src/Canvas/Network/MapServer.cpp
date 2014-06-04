#include "Network/Switch.h"
#include "Chat/Message.h"
#include "MapServer.h"
#include <QDebug>
#include "Log/MapLog.h"

MapServer::MapServer(QHash<QString, User *> *usersList) : ServerReceiver(usersList) {}
MapServer::~MapServer() {}

void MapServer::processNewMessage(Header header, QByteArray& data) {
	Message message(data);
	MapLog mapLog(*this);
	mapLog.setMessage(message);
	mapLog.setHeader(header);
	qDebug() << mapLog.toString();
	sendPacketToAll((quint16) TargetCode::MAP_CLIENT, header.getCode(), message);
}
