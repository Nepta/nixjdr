#ifndef CmdWhisper_H
#define CmdWhisper_H

#include "AbstractCmd.h"

class CmdWhisper : public AbstractCmd
{
public:
    CmdWhisper();

    void execute(Header &header, QString &arg);
    QString getHelp();
};

#endif // CmdWhisper_H
