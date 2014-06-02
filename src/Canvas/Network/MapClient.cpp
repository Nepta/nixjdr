#include "Network/Switch.h"

#include "Chat/Message.h"

#include "MapClient.h"
#include "Common.h"

MapClient::MapClient(User *user, QHash<QString, User *> *usersList) :
    ClientReceiver(user, usersList)
{
}

MapClient::~MapClient() {}

void MapClient::processNewMessage(Header header, QByteArray& data) {
    // TODO
}

void MapClient::sendMessageToServer(const QString& msg) {
    QString strippedMsg = msg;
    QString action = Common::extractFirstWord(strippedMsg);
    Message message(msg);

    if (action == "addSprite") {
        TargetCode target = TargetCode::MAP_SERVER;
        quint16 mapCode = (quint16) MapCodes::ADD_SPRITE;

        sendPacketToServer(mapCode, (quint16) target, message);
    }
}

void MapClient::addMapToList(Map* map) {
    m_MapsList.append(map);
}
