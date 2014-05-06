#ifndef CHATCMDWHISPER_H
#define CHATCMDWHISPER_H

#include "abstractchatcmd.h"

class ChatCmdWhisper : public AbstractChatCmd
{
public:
    ChatCmdWhisper();

    void execute(ChatHeader &header, QString &arg);
    QString getHelp();
};

#endif // CHATCMDWHISPER_H
