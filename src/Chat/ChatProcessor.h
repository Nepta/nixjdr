#ifndef CHATPROCESSOR_H
#define CHATPROCESSOR_H

#include <QString>
#include "Commands/Commands.h"
class ChatProcessor
{
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

        /**
         * @brief sendMessageToChatUi   Transmits a message that will be displayed in the chat
         * @param msg   Reference to the message to transmit
         */
        virtual void sendMessageToChatUi(const QString &msg) = 0;
};

#endif // CHATPROCESSOR_H
