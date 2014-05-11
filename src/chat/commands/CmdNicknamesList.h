#ifndef CMDNICKNAMESLIST_H
#define CMDNICKNAMESLIST_H

#include "AbstractCmd.h"

class CmdNicknamesList : public AbstractCmd
{
public:
    CmdNicknamesList();
    void execute(ChatHeader &, QString &);
    void executeOnUser(User *user);
    QString getHelp();
};

#endif // CMDNICKNAMESLIST_H
