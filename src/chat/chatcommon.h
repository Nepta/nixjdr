#ifndef CHATCOMMON_H
#define CHATCOMMON_H

#include <QtNetwork>
#include <QHash>
#include "commands/chatcmds.h"
#include "chatheader.h"

class ChatCommon
{

public:
    /**
     * @brief ChatCommon    Default constructor
     */
    ChatCommon();

    /**
     * @brief preparePacket     Prepare a packet with:
     * firstly, the packet's size,
     * secondly, the command's code,
     * thirdly, the message itself
     * @param msg   Reference to the raw message to transform
     * @return  The prepared packet
     */
    static QByteArray preparePacket(const QString &msg);

    /**
     * @brief preparePacket     Prepares a packet of which the code is known
     * @param cmdCode   known code
     * @param msg   Reference to the message to transfer, stripped of the command
     * @return  a fully prepared packet
     */
    static QByteArray preparePacket(ChatCodes cmdCode, const QString &msg);

    /**
     * @brief translateCommandToCode    Finds out if the user specified a command for his message.
     * If he didn't, interprets it as a USERCMD_MESSAGE
     * @param msg   Reference to the message to interpret
     * @return      The command's code
     */
    static ChatCodes translateCommandToCode(const QString &msg);

    /**
     * @brief stripCommandFromMessage   strips the message of its command
     * @param msg   Reference to the message to strip
     * @return  The stripped message
     */
    static QString stripCommandFromMessage(const QString &msg);

    /**
     * @brief extractFirstWord      Finds the first word in a message, strips it from the message
     * and returns that first word. Modifies the message in the process.
     * @param msg   Reference to the message from which you want to extract the first word
     * @return      Message's first word
     */
    static QString extractFirstWord(QString &msg);

    /**
     * @brief messageReadyToReceive     Determines wether a socket's message was fully received or not
     * @param socket    Socket to listen to
     * @param header    Reference to the message's header
     * @param msg       Reference to the message contained by the socket
     * @return          True if the message was fully received, and false if it was not.
     */
    static bool messageReadyToReceive(QTcpSocket *socket, ChatHeader &header,
                                      QString &msg);
};

#endif // CHATCOMMON_H
