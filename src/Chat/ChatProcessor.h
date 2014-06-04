#ifndef CHATPROCESSOR_H
#define CHATPROCESSOR_H

#include <QString>

#include "Commands/Commands.h"

class ChatProcessor
{
    public:
        ChatProcessor(){}
        virtual ~ChatProcessor(){}

        Commands *getCommands();

    protected:
        Commands m_Commands;

        /**
         * @brief sendMessageToChatUi Transmits a message that will be displayed in the chat.
         * @param msg Message to transmit.
         * @remarks Ensures that both ChatClient and ChatServer implements the sendMessageToChatUi()
         * signal. The signal is not declared here because it would mean ChatProcessor inherits
         * QObject. ChatClient and ChatServer are already inheriting QObject from other classes,
         * and QObject cannot be inherited more than once.
         */
        virtual void sendMessageToChatUi(const QString &msg) = 0;
};

#endif // CHATPROCESSOR_H
