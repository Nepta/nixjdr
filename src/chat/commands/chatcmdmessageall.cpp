#include "chatcmdmessageall.h"
#include "chatcmds.h"

ChatCmdMessageAll::ChatCmdMessageAll()
{
}

void ChatCmdMessageAll::execute(ChatHeader &header, QString &arg) {
    QString namedMessage = QString("[<strong>%1</strong>]: %2")
                       .arg(header.getSocketUserNickname())
                       .arg(arg);

    emit cmdSendPacketToAll(ChatCodes::SRVCMD_MESSAGE, namedMessage);
}

QString ChatCmdMessageAll::getHelp() {
    return NULL;
}
