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

protected:
    ChatCmds m_ChatCmds;

protected slots:
    virtual void processNewMessage(ChatHeader header, QString message) = 0;
};

#endif // CHATPROCESSOR_H