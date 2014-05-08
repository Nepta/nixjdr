#ifndef CHATCMDROLL_H
#define CHATCMDROLL_H

#include "abstractchatcmd.h"

class ChatCmdRoll:public AbstractChatCmd
{
public:
    ChatCmdRoll();

    void execute(ChatHeader &header, QString &arg);
    QString getHelp();

private :
    QString extractDice(QString dice);
    QString rollDice(int X, int Y);
};


#endif // CHATCMDROLL_H
