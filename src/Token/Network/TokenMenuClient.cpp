#include "TokenMenuClient.h"

TokenMenuClient::TokenMenuClient(User *user, QHash<QString, User *> *usersList) :
    SenderClient(user, usersList)
{}

TokenMenuClient::~TokenMenuClient() {}

void TokenMenuClient::processNewData(Header header, QByteArray &data) {
    // TODO
}

void TokenMenuClient::sendMessageToServer(const QString& msg) {
    // TODO
}
