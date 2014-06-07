#include "TokenMenuServer.h"

TokenMenuServer::TokenMenuServer(QHash<QString, User *> *usersList) :
    SenderServer(usersList)
{
}

TokenMenuServer::~TokenMenuServer() {}

void TokenMenuServer::processNewData(Header header, QByteArray& data) {
    // TODO
}
