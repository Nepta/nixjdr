#ifndef CHATCMDMESSAGEALL_H
#define CHATCMDMESSAGEALL_H

#include "abstractchatcmd.h"

class ChatCmdMessageAll : public AbstractChatCmd
{
public:
    ChatCmdMessageAll();

    void execute(ChatHeader &header, QString &arg);
    QString getHelp();
};

#endif // CHATCMDMESSAGEALL_H
