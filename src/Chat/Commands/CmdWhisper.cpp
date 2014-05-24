#include <QString>
#include <QRegExp>

#include "CmdWhisper.h"
#include "Common.h"
#include "Commands.h"

CmdWhisper::CmdWhisper()
{
}

void CmdWhisper::execute(Header &header, QString &arg) {
    QString strippedMsg, sender;
    strippedMsg = arg;

    sender = header.getSocketUserNickname();

    QList<QString> targetList = extractTargetList(strippedMsg);

    foreach (QString target, targetList) {

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
}

QString CmdWhisper::getHelp() {
    return tr("/whisper utilisateur message - Envoie un message à utilisateur");
}

QList<QString> CmdWhisper::extractTargetList(QString &message){

    QList<QString> targetList;

    targetList.append(Common::extractFirstWord(message));

    QString testString = message;
    QString firstOfTestString = Common::extractFirstWord(testString);

    while(!message.isNull() &&  firstOfTestString.at(0) == '|'){
        QString currentFirstWord = Common::extractFirstWord(message);
        if(firstOfTestString.length()>1 && firstOfTestString.at(1).isLetterOrNumber()){
            targetList.append(currentFirstWord.right(currentFirstWord.length()-1));
        }
        else{
            targetList.append(Common::extractFirstWord(message));
            testString = message;
        }
        firstOfTestString = Common::extractFirstWord(testString);
    }

    return targetList;
}
