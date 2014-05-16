#include "CmdMessageall.h"
#include "Commands.h"

CmdMessageAll::CmdMessageAll()
{
}

void CmdMessageAll::execute(Header &header, QString &arg) {
    Message namedMessage(QString("[<strong>%1</strong>]: %2")
                         .arg(header.getSocketUserNickname())
                         .arg(arg)
    );
    emit cmdSendPacketToAll(TargetCode::CHAT_CLIENT, ChatCodes::SRVCMD_MESSAGE, namedMessage);
}

QString CmdMessageAll::getHelp() {
    return NULL;
}
