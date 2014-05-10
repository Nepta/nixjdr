#include "chatcmdmessageui.h"

ChatCmdMessageUI::ChatCmdMessageUI()
{
}

void ChatCmdMessageUI::execute(ChatHeader &, QString &arg) {
    emit cmdSendMessageToUI(arg);
}

QString ChatCmdMessageUI::getHelp() {
    return NULL;
}
