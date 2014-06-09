#include "TurnMenuClient.h"

TurnMenuClient::TurnMenuClient(User *user, QHash<QString, User *> *usersList, TurnMenu *turnMenu) :
    SenderClient(user, usersList)
{
    m_TurnMenu = turnMenu;
}

TurnMenuClient::~TurnMenuClient() {}

void TurnMenuClient::processNewData(Header header, QByteArray &data) {
    // TODO
}

void TurnMenuClient::sendMessageToServer(const QString& msg, quint16 code) {
    // TODO
}
