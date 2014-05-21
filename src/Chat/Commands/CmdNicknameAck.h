#ifndef CmdNicknameAck_H
#define CmdNicknameAck_H

#include "AbstractCmd.h"

class CmdNicknameAck : public AbstractCmd
{
public:
    CmdNicknameAck();

    void execute(Header &, QString &arg);
    QString getHelp();
};

#endif // CmdNicknameAck_H
