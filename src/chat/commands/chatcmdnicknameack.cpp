#include "chatcmdnicknameack.h"
#include "../chatcommon.h"

ChatCmdNicknameAck::ChatCmdNicknameAck()
{
}

void ChatCmdNicknameAck::execute(ChatHeader &header, QString &arg) {
    QString newNickname = arg;
    QString oldNickname;

    oldNickname = ChatCommon::extractFirstWord(newNickname);

    User* user = AbstractChatCmd::getUsersListClient()->value(oldNickname);
    user->setNickname(newNickname);
    AbstractChatCmd::getUsersListClient()->remove(oldNickname);
    AbstractChatCmd::getUsersListClient()->insert(newNickname, user);

    emit cmdSendMessageToUI(tr("Vous avez changé votre peudo en %1").arg(newNickname));
}

QString ChatCmdNicknameAck::getHelp() {
    return NULL;
}
