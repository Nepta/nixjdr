#include "abstractchatcmd.h"

QHash<QString, User *> *AbstractChatCmd::s_ListUsers = NULL;

AbstractChatCmd::AbstractChatCmd() {

}

void AbstractChatCmd::setListUsers(QHash<QString, User *> *listUsers) {
    AbstractChatCmd::s_ListUsers = listUsers;
}

QHash<QString, User *> *AbstractChatCmd::getListUsers() {
    return AbstractChatCmd::s_ListUsers;
}
