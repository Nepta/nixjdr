#include "CmdNicknamesList.h"
#include "Commands.h"

CmdNicknamesList::CmdNicknamesList()
{
}

void CmdNicknamesList::execute(Header &, QString &) {
}

void CmdNicknamesList::executeOnUser(User *user) {
    QStringList nicknamesList = AbstractCmd::getUsersListServer()->keys();
    Message nicknames(nicknamesList.join(" "));

    emit cmdSendPacketToOne(
        TargetCode::CHAT_CLIENT,
        ChatCodes::SRVCMD_LIST,
        nicknames,
        user->getNickname());
}

QString CmdNicknamesList::getHelp() {
    return NULL;
}
