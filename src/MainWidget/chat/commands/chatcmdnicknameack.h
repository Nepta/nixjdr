#ifndef CHATCMDNICKNAMEACK_H
#define CHATCMDNICKNAMEACK_H

#include "abstractchatcmd.h"

class ChatCmdNicknameAck : public AbstractChatCmd
{
public:
    ChatCmdNicknameAck();

    void execute(ChatHeader &header, QString &arg);
    QString getHelp();
};

#endif // CHATCMDNICKNAMEACK_H
