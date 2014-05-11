#ifndef CMDNICKNAMESLISTACK_H
#define CMDNICKNAMESLISTACK_H

#include "AbstractCmd.h"

class CmdNicknamesListAck : public AbstractCmd
{
public:
    CmdNicknamesListAck();
    void execute(ChatHeader &, QString &arg);
    QString getHelp();
};

#endif // CMDNICKNAMESLISTACK_H
