#ifndef CMDNICKNAMESLIST_H
#define CMDNICKNAMESLIST_H

#include "abstractchatcmd.h"

class CmdNicknamesList : public AbstractChatCmd
{
public:
    CmdNicknamesList();
    void execute(ChatHeader &, QString &);
    void executeOnUser(User *user);
    QString getHelp();
};

#endif // CMDNICKNAMESLIST_H
