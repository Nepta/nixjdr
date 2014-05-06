#include <QString>
#include "chatcmdwhisper.h"
#include "chatcmds.h"
#include "../chatcommon.h"

ChatCmdWhisper::ChatCmdWhisper()
{
}

void ChatCmdWhisper::execute(ChatHeader &header, QString &arg) {
    QString strippedMsg, msgSender, msgTarget,
            sender, target;

    strippedMsg = arg;
    sender = header.getSocketUserNickname();
    target = ChatCommon::extractFirstWord(strippedMsg);

    if (AbstractChatCmd::getUsersListServer()->contains(target)) {
        msgTarget = tr("[%1] chuchote: %2")
                .arg(sender)
                .arg(strippedMsg);

        msgSender = tr("à [%1]: %2")
                .arg(target)
                .arg(strippedMsg);

        emit cmdSendPacketToOne(ChatCodes::SRVCMD_WHISPER_REP, msgTarget, target);
        emit cmdSendPacketToOne(ChatCodes::SRVCMD_WHISPER_REP, msgSender, sender);
    }
    else {
        QString errmsg = tr("%1 n'existe pas.")
                         .arg(target);

        emit cmdSendPacketToOne(ChatCodes::SRVCMD_MESSAGE, errmsg, sender);
    }
}

QString ChatCmdWhisper::getHelp() {
    return tr("/whisper utilisateur message - Envoie un message à utilisateur");
}
