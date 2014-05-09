#include "chatcmdroll.h"
#include "chat/chatcommon.h"
#include "chatcmdwhisper.h"

ChatCmdRoll::ChatCmdRoll(QHash<ChatCodes, AbstractChatCmd *> &userCommands) {
    m_UserCommands = userCommands;
}

void ChatCmdRoll::execute(ChatHeader &header, QString &arg) {
    QString dice, sender, target, result, namedMessage, message;
    bool error;

    dice = ChatCommon::extractFirstWord(arg);
    target = arg;
    sender = header.getSocketUserNickname();
    result = ChatCmdRoll::extractDice(dice, error);

    namedMessage = QString("[<strong>%1</strong>]: %2")
                       .arg(sender)
                       .arg(result);

    message = QString("%1 %2").arg(target).arg(result);

    if(!error){
        if(target != ""){
            ChatCmdWhisper *cmd = dynamic_cast<ChatCmdWhisper*>(m_UserCommands.value(ChatCodes::USERCMD_WHISPER));
            cmd->execute(header, message);
        }
        else {
            emit cmdSendPacketToAll(ChatCodes::SRVCMD_MESSAGE, namedMessage);
        }
    }
    else{
        emit cmdSendPacketToOne(ChatCodes::SRVCMD_MESSAGE, result, header.getSocketUserNickname());
    }
}

QString ChatCmdRoll::extractDice(QString dice, bool &error) {
    QString parser;
    int X;
    int Y=1;
    int k=0;

    error = false;

    //suppression des espaces, consideres comme des 0
    dice.replace(" ", "");
    // format : XdY
    for(int i =0; i<dice.length(); i++){
        if(dice.at(i).isDigit()){
            parser = parser + dice.at(i);
        }
        else{
            if(i == 0 || dice.at(i)!='d' || k>0){
                error = true;
                return(tr("<em>format de /roll <X>d<Y> incorrect.</em>"));
            }
            else{
                if(parser.length()>5){
                    error = true;
                    return(tr("<em>nombre de dés trop grand</em>"));
                }
                X = parser.toInt();
                parser = "";
                k++;
            }
        }
    }
    if(parser == ""){
        error = true;
        return(tr("<em>merci de spécifier un type de dé</em>"));
    }

    if(Y == 0 || parser.length()>5){
        error = true;
        return (tr("<em>Forme de dé inexistante.</em>"));
    }

    if(X > 10000){
        error = true;
        return(tr("<em>nombre de dés trop grand</em>"));
    }

    Y = parser.toInt();
    return (dice + ": " + ChatCmdRoll::rollDice(X, Y));
}


QString ChatCmdRoll::rollDice(int X, int Y){
    QString result;
    int tot, rand;

    for(int i=0; i<X; i++){
        rand = (qrand() % Y) +1;
        result += QString::number(rand) + ", ";
        tot += rand;
    }


    if(X>100){
        return tr("total :") + QString::number(tot);
    }
    else{
        return (result + tr("total : ") + QString::number(tot));
    }
}


QString ChatCmdRoll::getHelp() {
    return NULL;
}
