#ifndef CHATPROCESSOR_H
#define CHATPROCESSOR_H

#include <QObject>
#include "commands/chatcmds.h"

class ChatProcessor : public QObject
{
    Q_OBJECT

public:
    ChatProcessor(){}

    virtual ~ChatProcessor(){}

    /**
     * @brief getChatCmds   Gives access to the commands
     * @return &m_ChatCmds
     */
    ChatCmds *getChatCmds();

protected:
    ChatCmds m_ChatCmds;

protected slots:
    virtual void processNewMessage(ChatHeader header, QString message) = 0;
};

#endif // CHATPROCESSOR_H
