#ifndef CmdMessageall_H
#define CmdMessageall_H

#include "AbstractCmd.h"

class CmdMessageAll : public AbstractCmd
{
public:
    CmdMessageAll();

    void execute(ChatHeader &header, QString &arg);
    QString getHelp();
};

#endif // CmdMessageall_H
