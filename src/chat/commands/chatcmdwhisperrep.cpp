#include "chatcmdwhisperrep.h"

ChatCmdWhisperRep::ChatCmdWhisperRep()
{
}

void ChatCmdWhisperRep::execute(ChatHeader &header, QString &arg) {
    QString formattedMsg = QString("<div style=\" color:#9E6B94;\">%1</div>")
                           .arg(arg);

    emit cmdSendMessageToUI(formattedMsg);
}

QString ChatCmdWhisperRep::getHelp() {
    return NULL;
}
