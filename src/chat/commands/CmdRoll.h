#ifndef CmdRoll_H
#define CmdRoll_H

#include "AbstractCmd.h"

class CmdRoll:public AbstractCmd
{
public:
    CmdRoll(QHash<ChatCodes, AbstractCmd *> &userCommands);

    void execute(ChatHeader &header, QString &arg);
    QString getHelp();

private :
    QString extractDice(QString dice, bool &error);
    int rollDice(int X, int Y, bool addition, QString &totalResultString);
    QHash<ChatCodes, AbstractCmd *> m_UserCommands;
};


#endif // CmdRoll_H
