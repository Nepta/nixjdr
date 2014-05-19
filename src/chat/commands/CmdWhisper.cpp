#include <QString>
#include "CmdWhisper.h"
#include "Common.h"
#include "Commands.h"

CmdWhisper::CmdWhisper()
{
}

void CmdWhisper::execute(Header &header, QString &arg) {
    QString strippedMsg, sender, target;
    strippedMsg = arg;

    sender = header.getSocketUserNickname();
    target = Common::extractFirstWord(strippedMsg);

    if (AbstractCmd::getUsersListServer()->contains(target)) {
        Message msgTarget(tr("[%1] chuchote: %2")
            .arg(sender)
            .arg(strippedMsg)
        );

        Message msgSender(tr("à [%1]: %2")
                .arg(target)
                .arg(strippedMsg)
        );

        emit cmdSendPacketToOne(
            TargetCode::CHAT_CLIENT,
            ChatCodes::SRVCMD_WHISPER_REP,
            msgTarget,
            target
        );

        if(target != sender) {
            emit cmdSendPacketToOne(
                TargetCode::CHAT_CLIENT,
                ChatCodes::SRVCMD_WHISPER_REP,
                msgSender,
                sender
            );
        }
    }
    else {
        Message errmsg(tr("%1 n'existe pas.")
            .arg(target)
        );
        emit cmdSendPacketToOne(
            TargetCode::CHAT_CLIENT,
            ChatCodes::SRVCMD_MESSAGE,
            errmsg,
            sender
        );
    }
}

QString CmdWhisper::getHelp() {
    return tr("/whisper utilisateur message - Envoie un message à utilisateur");
}
