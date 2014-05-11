#ifndef CmdWhisperRep_H
#define CmdWhisperRep_H

#include "AbstractCmd.h"

class CmdWhisperRep : public AbstractCmd
{
public:
    CmdWhisperRep();

    void execute(ChatHeader &, QString &arg);
    QString getHelp();
};

#endif // CmdWhisperRep_H
