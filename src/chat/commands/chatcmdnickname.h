#ifndef CHATCMDNICKNAME_H
#define CHATCMDNICKNAME_H

#include "abstractchatcmd.h"

class ChatCmdNickname : public AbstractChatCmd
{
public:
    ChatCmdNickname();

    void execute(ChatHeader &header, QString &arg);
    void executeOnUser(User *newUser, QString currentNickname, QString oldNickname, bool isNew);
    QString getHelp();
    QString verifyAndGetNickname(QString nickname);
};

#endif // CHATCMDNICKNAME_H
