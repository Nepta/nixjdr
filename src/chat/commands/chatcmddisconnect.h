#ifndef CHATCMDDISCONNECT_H
#define CHATCMDDISCONNECT_H

#include <QString>
#include "chat/chatheader.h"
#include "abstractchatcmd.h"

class ChatCmdDisconnect : public AbstractChatCmd
{
public:
    ChatCmdDisconnect();

    void execute(ChatHeader &, QString &arg);
    QString getHelp();
};

#endif // CHATCMDDISCONNECT_H
