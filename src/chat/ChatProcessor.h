#ifndef CHATPROCESSOR_H
#define CHATPROCESSOR_H

#include <QObject>
#include <QString>
#include "commands/Commands.h"
#include "ChatHeader.h"

class ChatProcessor : public QObject
{
    Q_OBJECT

public:
    ChatProcessor(){}

    virtual ~ChatProcessor(){}

    /**
     * @brief getCommands   Gives access to the commands
     * @return &m_Commands
     */
    Commands *getCommands();

protected:
    Commands m_Commands;

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
