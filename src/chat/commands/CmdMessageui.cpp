#include "CmdMessageui.h"

CmdMessageUI::CmdMessageUI()
{
}

void CmdMessageUI::execute(ChatHeader &, QString &arg) {
    emit cmdSendMessageToChatUi(arg);
}

QString CmdMessageUI::getHelp() {
    return NULL;
}
