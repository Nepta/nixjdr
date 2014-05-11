#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QtGui>
#include <QtNetwork>
#include "commands/chatcmds.h"
#include "chatprocessor.h"
#include "user.h"

class ChatClient : public ChatProcessor
{
    Q_OBJECT

/*-------------------------------------------------------------------------------------------------------*/
public:
    /**
     * @brief ChatClient::ChatClient Default constructor, connects signals and initializes the userlist
     */
    ChatClient();

    ~ChatClient();

    /**
     * @brief ChatClient::ChatClient    Calls the default constructor, and connects to the server's
     *  IP and port
     * @param serverIP  Reference to the IP of the server you want to connect to
     * @param serverPort    Reference to the port to use on the server you want to connect to
     */
    ChatClient(const QString &serverIP, const quint16 &serverPort);

    /**
     * @brief ChatClient::connection    Connects the client to the specified host (IP and port).
     * @param serverIP  IP of the server you want to connect to
     * @param serverPort    Port to use on the server you want to connect to
     */
    void connection(const QString &serverIP, const quint16 &serverPort);

    /**
     * @brief ChatClient::sendMessageToServer   Sends the message to the server in order
     * to broadcast it to all the users.
     * @param msg   Reference to the message to send
     */
    void sendMessageToServer(const QString &msg);

    /**
     * @brief getUser   Returns the user associated with the client
     * @return  A pointer towards the current client's user
     */
    User *getUser();

/*-------------------------------------------------------------------------------------------------------*/
signals:
    /**
     * @brief sendMessageToUI   Transmits a message that will be displayed in the chat
     * @param msg   Reference to the message to the message to transmit
     */
    void sendMessageToUI(const QString &msg);

/*-------------------------------------------------------------------------------------------------------*/
private slots:
    /**
     * @brief socketError   Displays a message depending on the error's type
     * @param error     error to analyse
     */
    void socketError(QAbstractSocket::SocketError error);

    /**
     * @brief processNewMessage     Interprets incoming server message's commands
     * @param header    message's header, contains the command to interpret
     * @param message   message to process
     */
    void processNewMessage(ChatHeader header, QString message);

    /**
     * @brief clientConnected   Emits a message in the chatwindow indicating that the user successfully connected
     */
    void clientConnected();

    /**
     * @brief clientDisconnected    Emits a message in the chatwindow indicating that the user was disconnected
     */
    void clientDisconnected(User &);

/*-------------------------------------------------------------------------------------------------------*/
private:
    User *m_User;
    QHash<QString, User *> m_UsersList;
};

#endif // CHATCLIENT_H
