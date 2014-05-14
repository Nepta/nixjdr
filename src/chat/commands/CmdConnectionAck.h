#ifndef CMDCONNECTIONACK_H
#define CMDCONNECTIONACK_H

#include "AbstractCmd.h"

class CmdConnectionAck : public AbstractCmd
{
public:
    CmdConnectionAck();

    void execute(ChatHeader &, QString &);
    QString getHelp();
};

#endif // CMDCONNECTIONACK_H
