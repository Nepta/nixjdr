#include "Network/Switch.h"
#include "Chat/Message.h"
#include "MapServer.h"
#include <QDebug>

MapServer::MapServer(QHash<QString, User *> *usersList) : ServerReceiver(usersList) {}
MapServer::~MapServer() {}

void MapServer::processNewMessage(Header header, QByteArray& data) {
	Message message(data);

	switch(header.getCode()){
		case 1:
			qDebug() << "addSpriteAction(" + message.getString() + ")";
			break;

		case 2:
			qDebug() << "removeSpriteAction(" + message.getString() + ")";
			break;

		case 3:
			qDebug() << "removeAllFoWAction(" + message.getString() + ")";
			break;

		default:
			break;
	}

	sendPacketToAll((quint16) TargetCode::MAP_CLIENT, header.getCode(), message);
}
