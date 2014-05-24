#include "Chat/Commands/Commands.h"
#include "CmdRoll.h"
#include "CmdWhisper.h"

CmdRoll::CmdRoll(QHash<ChatCodes, AbstractCmd *> &userCommands) {
    m_UserCommands = userCommands;
}

void CmdRoll::execute(Header &header, QString &arg) {
    QString dice, sender, target, result;
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

    result = CmdRoll::extractDice("0"+dice, error);

    if(!error){
        if(target != ""){
            QString msg = QString("%1 %2")
                .arg(target)
                .arg(result);
            CmdWhisper *cmd = dynamic_cast<CmdWhisper*>(
                        m_UserCommands.value(ChatCodes::USERCMD_WHISPER));
            cmd->execute(header, msg);
        }
        else {
            Message namedMessage(QString("[<strong>%1</strong>]: %2")
               .arg(sender)
               .arg(result)
            );
            emit cmdSendPacketToAll(
                TargetCode::CHAT_CLIENT,
                ChatCodes::SRVCMD_MESSAGE,
                namedMessage
            );
        }
    }
    else{
        Message resultMsg(result);
        emit cmdSendPacketToOne(
            TargetCode::CHAT_CLIENT,
            ChatCodes::SRVCMD_MESSAGE,
            resultMsg,
            header.getSocketUserNickname()
        );
    }
}

QString CmdRoll::extractDice(QString dice, bool &error) {
    QString parser, resultString, returnString;
    int X, Y, result, addToResult;
    bool addition = true;
    X = -1;
    addToResult = 0;
    result = 0;
    Y=1;

    error = false;

    dice.append("+");

    // format : XdY
    for(int i =0; i<dice.length(); i++){
        if(i>0 && dice.at(i-1)=='+'){
            addition = true;
        }
        else if(i>0 && dice.at(i-1)== '-'){
            addition = false;
        }
        if(dice.at(i).isDigit()){
            parser = parser + dice.at(i);
        }
        else{
            if(i!=0 && dice.at(i)=='d' && parser.length()<5 && X == -1){
                X=parser.toInt();
                parser ="";
            }
            else if(i!=0 && (dice.at(i)=='+' || dice.at(i) =='-') && parser.length()<5) {
                if( X==-1){
                    if(addition) {
                        addToResult += parser.toInt();
                    }
                    else{
                        addToResult -=parser.toInt();
                    }
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
                    result +=CmdRoll::rollDice(X, Y, addition, resultString);
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


int CmdRoll::rollDice(int X, int Y, bool addition, QString &totalResultString){
    QString result, diceType;
    int rand;
    int tot= 0;

    for(int i=0; i<X; i++){
        rand = (qrand() % Y) +1;
        result += QString::number(rand) + ", ";
        tot += rand;
    }

    diceType = QString("%1d%2").arg(QString::number(X)).arg(QString::number(Y));
    if(!addition){
        tot = -tot;
        diceType.prepend("-");
    }
    diceType.prepend("<strong>").append("</strong>");

    if(X>100){
        totalResultString += QString("%1 total: %2").arg(diceType).arg(QString::number(tot));
    }
    else{
        totalResultString += QString("%1 résultats: %2 <em>sous total:</em> %3\n").arg(diceType).arg(result).arg(QString::number(tot));
    }
    return tot;
}


QString CmdRoll::getHelp() {
    return tr("/roll &lt;nb&gt;d&lt;n&gt; - Roule nb dés de valeur max n");
}
