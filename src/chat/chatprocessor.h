#ifndef CHATPROCESSOR_H
#define CHATPROCESSOR_H

#include <QObject>
#include <QString>
#include "commands/chatcmds.h"
#include "chatheader.h"

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

signals:
    /**
     * @brief sendMessageToChatUi   Transmits a message that will be displayed in the chat
     * @param msg   Reference to the message to transmit
     */
    void sendMessageToChatUi(const QString &msg);
};

#endif // CHATPROCESSOR_H
