#include "TurnMenuServer.h"

TurnMenuServer::TurnMenuServer(QHash<QString, User *> *usersList) :
    SenderServer(usersList)
{}

TurnMenuServer::~TurnMenuServer() {}

void TurnMenuServer::processNewData(Header header, QByteArray& data) {
    // TODO
}
