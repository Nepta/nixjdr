#ifndef CLIENT_H
#define CLIENT_H

#include "Switch.h"
#include "User.h"

class Client : public Switch
{
    Q_OBJECT

public:
    Client(User *user);
    ~Client();

   /**
    * @brief ChatClient::connection    Connects the client to the specified host (IP and port).
    * @param serverIP  IP of the server you want to connect to
    * @param serverPort    Port to use on the server you want to connect to
    */
   void connection(const QString &serverIP, const quint16 &serverPort);

   /**
    * @brief getUser   Returns the user associated with the client
    * @return  A pointer towards the current client's user
    */
   User *getUser();

private slots:
   /**
    * @brief socketError   Displays a message depending on the error's type
    * @param error     error to analyse
    */
   void socketError(QAbstractSocket::SocketError error);

   /**
    * @brief clientConnected   Emits a message in the chatwindow indicating that the user successfully connected
    */
   void clientConnected();

   /**
    * @brief clientDisconnected    Emits a message in the chatwindow indicating that the user was disconnected
    */
   void clientDisconnected(User &);

signals:
    void sendMessageToChatUi(const QString &msg);

private:
    User *m_User;
    QHash<QString, User *> m_UsersList;
};

#endif // CLIENT_H
