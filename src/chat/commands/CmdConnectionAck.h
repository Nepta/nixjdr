#ifndef CMDCONNECTIONACK_H
#define CMDCONNECTIONACK_H

#include "AbstractCmd.h"

class CmdConnectionAck : public AbstractCmd
{
public:
    CmdConnectionAck();

    void execute(Header &header, QString &);
    QString getHelp();
};

#endif // CMDCONNECTIONACK_H
