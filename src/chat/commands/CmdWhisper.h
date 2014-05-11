#ifndef CmdWhisper_H
#define CmdWhisper_H

#include "AbstractCmd.h"

class CmdWhisper : public AbstractCmd
{
public:
    CmdWhisper();

    void execute(ChatHeader &header, QString &arg);
    QString getHelp();
};

#endif // CmdWhisper_H
