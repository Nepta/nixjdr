#include "abstractchatcmd.h"

QHash<QString, User *> *AbstractChatCmd::s_UsersListClient = NULL;
QHash<QString, User *> *AbstractChatCmd::s_UsersListServer = NULL;

AbstractChatCmd::AbstractChatCmd() {

}

void AbstractChatCmd::setUsersListClient(QHash<QString, User *> *usersList) {
    AbstractChatCmd::s_UsersListClient = usersList;
}

QHash<QString, User *> *AbstractChatCmd::getUsersListClient() {
    return AbstractChatCmd::s_UsersListClient;
}

void AbstractChatCmd::setUsersListServer(QHash<QString, User *> *usersList) {
    AbstractChatCmd::s_UsersListServer = usersList;
}

QHash<QString, User *> *AbstractChatCmd::getUsersListServer() {
    return AbstractChatCmd::s_UsersListServer;
}

