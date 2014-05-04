#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QObject>
#include <QtNetwork>
#include "user.h"
#include "chatheader.h"
#include "chatcommon.h"

class ChatServer : public QObject
{
    Q_OBJECT

public:
    ChatServer();
    ~ChatServer();
    quint16 getPort();
    void init();

private slots:
    void newClientConnection();
    void userDisconnected(User &user);
    void processNewMessage(ChatHeader header, QString message);

signals:
    void sendMessageToUI(const QString &msg);

private:
    void sendPacketToAll(ChatCommon::commands code, QString message);
    void sendPacketToOne(ChatCommon::commands code, QString message,
                                     QString receiverNickname);
    void sendMessageToAll(ChatHeader &header, QString &message);
    QString verifyAndGetNickname(QString nickname);
    void cmdModifyNickname(ChatHeader &header, QString nickname);

    QTcpServer *server;
    QHash<QString, User *> listUsers;
};

#endif // CHATSERVER_H
