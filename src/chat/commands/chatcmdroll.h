#ifndef CHATCMDROLL_H
#define CHATCMDROLL_H

#include "abstractchatcmd.h"

class ChatCmdRoll:public AbstractChatCmd
{
public:
    ChatCmdRoll(QHash<ChatCodes, AbstractChatCmd *> &userCommands);

    void execute(ChatHeader &header, QString &arg);
    QString getHelp();

private :
    QString extractDice(QString dice, bool &error);
    int rollDice(int X, int Y, bool addition, QString &totalResultString);
    QHash<ChatCodes, AbstractChatCmd *> m_UserCommands;
};


#endif // CHATCMDROLL_H
