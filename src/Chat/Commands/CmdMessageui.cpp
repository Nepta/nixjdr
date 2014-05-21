#include "CmdMessageui.h"

CmdMessageUI::CmdMessageUI()
{
}

void CmdMessageUI::execute(Header &, QString &arg) {
    emit cmdSendMessageToChatUi(arg);
}

QString CmdMessageUI::getHelp() {
    return NULL;
}
