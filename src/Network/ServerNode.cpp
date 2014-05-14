#include "ServerNode.h"
#include "chat/ChatCommon.h"

ServerNode::ServerNode() {}

ServerNode::ServerNode(QTcpServer *server, QHash<QString, User *> usersList) {
    m_Server = server;
    m_UsersList = usersList;
}

void ServerNode::sendPacketToAll(quint16 code, QString message) {
    QByteArray packet;
    packet = ChatCommon::preparePacket(code, message);

    for (int i = 0; i < m_UsersList.values().size(); i++)
    {
        m_UsersList.values()[i]->getSocket()->write(packet);
    }
}

void ServerNode::sendPacketToOne(quint16 code, QString message, QString receiverNickname) {
    QByteArray packet;

    packet = ChatCommon::preparePacket(code, message);
    m_UsersList.value(receiverNickname)->getSocket()->write(packet);
}
