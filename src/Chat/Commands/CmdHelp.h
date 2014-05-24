#ifndef CMDHELP_H
#define CMDHELP_H

#include "AbstractCmd.h"
#include "Commands.h"

class CmdHelp : public AbstractCmd
{
public:
    CmdHelp(QHash<ChatCodes, AbstractCmd *> *commandsHash);

    void execute(Header &header, QString &);
    QString getHelp();
private:
    QHash<ChatCodes, AbstractCmd *> *m_CommandsHash;
};

#endif // CMDHELP_H
