#ifndef CmdMessageui_H
#define CmdMessageui_H

#include "AbstractCmd.h"

class CmdMessageUI : public AbstractCmd
{
public:
    CmdMessageUI();

    void execute(Header &, QString &arg);
    QString getHelp();
};

#endif // CmdMessageui_H
