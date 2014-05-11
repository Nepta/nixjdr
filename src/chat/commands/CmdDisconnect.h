#ifndef CHATCMDDISCONNECT_H
#define CHATCMDDISCONNECT_H

#include "AbstractCmd.h"

class CmdDisconnect : public AbstractCmd
{
public:
    CmdDisconnect();

    void execute(ChatHeader &, QString &arg);
    QString getHelp();
};

#endif // CHATCMDDISCONNECT_H
