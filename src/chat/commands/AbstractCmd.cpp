#include "AbstractCmd.h"

QHash<QString, User *> *AbstractCmd::s_UsersListClient = NULL;
QHash<QString, User *> *AbstractCmd::s_UsersListServer = NULL;

AbstractCmd::AbstractCmd() {

}

void AbstractCmd::setUsersListClient(QHash<QString, User *> *usersList) {
    AbstractCmd::s_UsersListClient = usersList;
}

QHash<QString, User *> *AbstractCmd::getUsersListClient() {
    return AbstractCmd::s_UsersListClient;
}

void AbstractCmd::setUsersListServer(QHash<QString, User *> *usersList) {
    AbstractCmd::s_UsersListServer = usersList;
}

QHash<QString, User *> *AbstractCmd::getUsersListServer() {
    return AbstractCmd::s_UsersListServer;
}

