#ifndef CMDNICKNAMESLIST_H
#define CMDNICKNAMESLIST_H

#include <QString>
#include "abstractchatcmd.h"
#include "chat/chatheader.h"

class CmdNicknamesList : public AbstractChatCmd
{
public:
    CmdNicknamesList();
    void execute(ChatHeader &header, QString &arg);
    void executeOnUser(User *user);
    QString getHelp();
};

#endif // CMDNICKNAMESLIST_H
