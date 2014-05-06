#ifndef CHATCMDWHISPERREP_H
#define CHATCMDWHISPERREP_H

#include "abstractchatcmd.h"

class ChatCmdWhisperRep : public AbstractChatCmd
{
public:
    ChatCmdWhisperRep();

    void execute(ChatHeader &header, QString &arg);
    QString getHelp();
};

#endif // CHATCMDWHISPERREP_H
