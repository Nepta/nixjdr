#include "chatcmdmessageui.h"

ChatCmdMessageUI::ChatCmdMessageUI()
{
}

void ChatCmdMessageUI::execute(ChatHeader &, QString &arg) {
    emit cmdsendMessageToChatUi(arg);
}

QString ChatCmdMessageUI::getHelp() {
    return NULL;
}
