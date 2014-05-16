#include "CmdWhisperRep.h"

CmdWhisperRep::CmdWhisperRep()
{
}

void CmdWhisperRep::execute(Header &, QString &arg) {
    QString formattedMsg = QString("<div style=\" color:#9E6B94;\">%1</div>")
                           .arg(arg);

    emit cmdSendMessageToChatUi(formattedMsg);
}

QString CmdWhisperRep::getHelp() {
    return NULL;
}
