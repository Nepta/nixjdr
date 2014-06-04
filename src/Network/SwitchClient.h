#ifndef SWITCHCLIENT_H
#define SWITCHCLIENT_H

#include "Database/Database.h"
#include "Token/TokenList.h"
#include "Switch.h"
#include "User.h"

class SwitchClient : public Switch
{
    Q_OBJECT

public:
    SwitchClient(User *user, Database *db, TokenList *tokenList);
    ~SwitchClient();

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

#endif // SWITCHCLIENT_H
