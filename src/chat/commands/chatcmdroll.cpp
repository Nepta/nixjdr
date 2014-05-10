#include "chatcmdroll.h"
#include "chat/chatcommon.h"
#include "chatcmdwhisper.h"

ChatCmdRoll::ChatCmdRoll(QHash<ChatCodes, AbstractChatCmd *> &userCommands) {
    m_UserCommands = userCommands;
}

void ChatCmdRoll::execute(ChatHeader &header, QString &arg) {
    QString dice, sender, target, result, namedMessage, message;
    bool error;
    int separatorIndex;

    arg.simplified();
    arg = arg.remove(' ');

    separatorIndex = arg.indexOf("|");

    sender = header.getSocketUserNickname();

    if(separatorIndex != -1){
        dice = arg.left(separatorIndex);
        target = arg.right(arg.length() - separatorIndex - 1);
    }
    else{
        dice = arg;
    }

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
    QString parser, resultString, returnString;
    int X, Y, result, addToResult;
    X = -1;
    addToResult = 0;
    result = 0;
    Y=1;

    error = false;

    dice.append("+");

    // format : XdY
    for(int i =0; i<dice.length(); i++){
        if(dice.at(i).isDigit()){
            parser = parser + dice.at(i);
        }
        else{
            if(i!=0 && dice.at(i)=='d' && parser.length()<5 && X == -1){
                X=parser.toInt();
                parser ="";
            }
            else if(i!=0 && dice.at(i)=='+' && parser.length()<5) {
                if( X==-1 ){
                    addToResult += parser.toInt();
                    parser ="";
                }
                else {
                    Y = parser.toInt();

                    if(Y == 0 || parser.length()>5){
                        error = true;
                        return (tr("<em>Forme de dé inexistante.</em>"));
                    }

                    if(X > 10000){
                        error = true;
                        return(tr("<em>nombre de dés trop grand</em>"));
                    }
                    result +=ChatCmdRoll::rollDice(X, Y, resultString);
                    X=-1;
                    Y=0;
                    parser ="";
                }
            }
            else{
                error = true;
                return(tr("<em>format de /roll [X] d [Y] [ | utilisateur] incorrect.</em>"));
            }
        }
    }
    result += addToResult;

    returnString = resultString;
    if(addToResult != 0){
        returnString += tr("<strong>Modificateur: </strong>" ) + QString::number(addToResult);
    }
    returnString += tr("\n<strong>Total: </strong>") + QString::number(result);

    return returnString;
}


int ChatCmdRoll::rollDice(int X, int Y, QString &totalResultString){
    QString result, diceType;
    int rand;
    int tot= 0;

    for(int i=0; i<X; i++){
        rand = (qrand() % Y) +1;
        result += QString::number(rand) + ", ";
        tot += rand;
    }

    diceType = "<strong>" + QString::number(X) + "d" + QString::number(Y) + "</strong>";
    if(X>100){
        totalResultString += diceType + tr(" total :") + QString::number(tot);
    }
    else{
        totalResultString += (diceType + tr(" résultats: ") + result + tr(" sous total: ") + QString::number(tot) + "\n");
    }
    return tot;
}


QString ChatCmdRoll::getHelp() {
    return NULL;
}
