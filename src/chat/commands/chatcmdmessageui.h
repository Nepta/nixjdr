#ifndef CHATCMDMESSAGEUI_H
#define CHATCMDMESSAGEUI_H

#include "abstractchatcmd.h"

class ChatCmdMessageUI : public AbstractChatCmd
{
public:
    ChatCmdMessageUI();

    void execute(ChatHeader &, QString &arg);
    QString getHelp();
};

#endif // CHATCMDMESSAGEUI_H
