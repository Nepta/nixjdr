#include "chatcmdnicknameack.h"
#include "../chatcommon.h"

ChatCmdNicknameAck::ChatCmdNicknameAck()
{
}

void ChatCmdNicknameAck::execute(ChatHeader &header, QString &arg) {
    QString newNickname = arg;
    QString oldNickname;

    oldNickname = ChatCommon::extractFirstWord(newNickname);

    AbstractChatCmd::getUsersListClient()->value(oldNickname)
                                   ->setNickname(newNickname);

    emit cmdSendMessageToUI(tr("Vous avez changé votre peudo en %1").arg(newNickname));
}

QString ChatCmdNicknameAck::getHelp() {
    return NULL;
}
