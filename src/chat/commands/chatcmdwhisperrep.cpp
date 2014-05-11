#include "chatcmdwhisperrep.h"

ChatCmdWhisperRep::ChatCmdWhisperRep()
{
}

void ChatCmdWhisperRep::execute(ChatHeader &, QString &arg) {
    QString formattedMsg = QString("<div style=\" color:#9E6B94;\">%1</div>")
                           .arg(arg);

    emit cmdsendMessageToChatUi(formattedMsg);
}

QString ChatCmdWhisperRep::getHelp() {
    return NULL;
}
