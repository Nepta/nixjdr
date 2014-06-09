#include "Network/Serializable/Message.h"
#include "Network/Switch.h"
#include "TurnMenuServer.h"

TurnMenuServer::TurnMenuServer(QHash<QString, User *> *usersList) :
    SenderServer(usersList)
{}

TurnMenuServer::~TurnMenuServer() {}

void TurnMenuServer::processNewData(Header header, QByteArray& data) {
    Message message(data);

    QList<User *> recipients = m_UsersList->values();
    recipients.removeOne(m_UsersList->value(header.getSocketUserNickname()));

    sendPacketToList((quint16) TargetCode::TURN_MENU_CLIENT, header.getCode(), message, recipients);
}
