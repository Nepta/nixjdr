#ifndef CMDNICKNAMESLISTACK_H
#define CMDNICKNAMESLISTACK_H

#include <QString>
#include "abstractchatcmd.h"
#include "chat/chatheader.h"

class CmdNicknamesListAck : public AbstractChatCmd
{
public:
    CmdNicknamesListAck();
    void execute(ChatHeader &header, QString &arg);
    QString getHelp();
};

#endif // CMDNICKNAMESLISTACK_H
