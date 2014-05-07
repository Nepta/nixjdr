#ifndef CHATCMDNICKNAME_H
#define CHATCMDNICKNAME_H

#include <QString>
#include "chat/chatheader.h"
#include "abstractchatcmd.h"

class ChatCmdNickname : public AbstractChatCmd
{
public:
    ChatCmdNickname();

    void execute(ChatHeader &header, QString &arg);
    void executeNewClientConnection(User *newUser);
    QString getHelp();
    QString verifyAndGetNickname(QString nickname);
};

#endif // CHATCMDNICKNAME_H
