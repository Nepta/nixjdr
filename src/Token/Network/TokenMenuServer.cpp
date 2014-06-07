#include "Network/Serializable/Message.h"
#include "Network/Switch.h"
#include "TokenMenuCodes.h"
#include "TokenMenuServer.h"

TokenMenuServer::TokenMenuServer(QHash<QString, User *> *usersList) :
    SenderServer(usersList)
{
}

TokenMenuServer::~TokenMenuServer() {}

void TokenMenuServer::processNewData(Header header, QByteArray& data) {
    Message message(data);

    // Creates a list of Users to whom the message must be transmitted excluding the sender of the
    // currently received data
    QList<User *> recipients = m_UsersList->values();
    recipients.removeOne(m_UsersList->value(header.getSocketUserNickname()));

    sendPacketToList((quint16) TargetCode::TOKEN_MENU_CLIENT, header.getCode(), message, recipients);
}
