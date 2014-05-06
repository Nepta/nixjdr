#include "chatcmdmessageui.h"

ChatCmdMessageUI::ChatCmdMessageUI()
{
}

void ChatCmdMessageUI::execute(ChatHeader &header, QString &arg) {
    emit cmdSendMessageToUI(arg);
}

QString ChatCmdMessageUI::getHelp() {
    return NULL;
}
