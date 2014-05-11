#include "CmdNicknamesList.h"
#include "Commands.h"

CmdNicknamesList::CmdNicknamesList()
{
}

void CmdNicknamesList::execute(ChatHeader &, QString &) {
}

void CmdNicknamesList::executeOnUser(User *user) {
    QStringList nicknamesList = AbstractCmd::getUsersListServer()->keys();
    QString nicknames = nicknamesList.join(" ");

    emit cmdSendPacketToOne(ChatCodes::SRVCMD_LIST, nicknames, user->getNickname());
}

QString CmdNicknamesList::getHelp() {
    return NULL;
}
