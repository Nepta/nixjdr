#include "CmdNicknamesList.h"
#include "chatcmds.h"

CmdNicknamesList::CmdNicknamesList()
{
}

void CmdNicknamesList::execute(ChatHeader &, QString &) {
}

void CmdNicknamesList::executeOnUser(User *user) {
    QStringList nicknamesList = AbstractChatCmd::getUsersListServer()->keys();
    QString nicknames = nicknamesList.join(" ");

    emit cmdSendPacketToOne(ChatCodes::SRVCMD_LIST, nicknames, user->getNickname());
}

QString CmdNicknamesList::getHelp() {
    return NULL;
}
