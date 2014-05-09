#include "chatcmdroll.h"
#include "chat/chatcommon.h"
#include "chatcmdwhisper.h"

ChatCmdRoll::ChatCmdRoll(QHash<ChatCodes, AbstractChatCmd *> &userCommands) {
    m_UserCommands = userCommands;
}

void ChatCmdRoll::execute(ChatHeader &header, QString &arg) {
    QString dice, sender, target, result, namedMessage, message;

    dice = ChatCommon::extractFirstWord(arg);
    sender = header.getSocketUserNickname();
    target = arg;
    result = ChatCmdRoll::extractDice(dice);

    namedMessage = QString("[%1]: %2")
                       .arg(header.getSocketUserNickname())
                       .arg(result);

    message = QString("%1 %2").arg(target).arg(result);

    ChatCmdWhisper *cmd = dynamic_cast<ChatCmdWhisper*>(m_UserCommands.value(ChatCodes::USERCMD_WHISPER));

    if(result != "!"){
        if(target != ""){
            cmd->execute(header, message);
        }
        else{
            emit cmdSendPacketToOne(ChatCodes::SRVCMD_MESSAGE, namedMessage, header.getSocketUserNickname());
        }
    }
    else{
        emit cmdSendPacketToOne(ChatCodes::SRVCMD_MESSAGE, tr("format de /roll <X>d<Y> incorrect."), header.getSocketUserNickname());
    }
}

QString ChatCmdRoll::extractDice(QString dice){
    int X;
    int Y=1;
    QString parser;
    int k=0;

    //suppression des espaces, consideres comme des 0
    dice.replace(" ", "");
    // format : XdY
    for(int i =0; i<dice.length(); i++){
        if(dice.at(i).isDigit()){
            parser = parser + dice.at(i);
        }
        else{
            if(i == 0 || dice.at(i)!='d' || k>0){
                return("!");
            }
            else{
                if(parser.length()>5){
                    return(tr("nombre de dés trop grand"));
                }
                X = parser.toInt();
                parser = "";
                k++;
            }
        }
    }
    if(parser == ""){
        return(tr("merci de spécifier un type de dé"));
    }

    if(Y == 0 || parser.length()>5){
        return (tr("Forme de dé inexistante."));
    }

    if(X > 10000){
        return(tr("nombre de dés trop grand"));
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
