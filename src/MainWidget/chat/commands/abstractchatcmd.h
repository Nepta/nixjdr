#ifndef ABSTRACTCHATCMD_H
#define ABSTRACTCHATCMD_H

#include <QString>
#include <QObject>
#include <QHash>
#include "user.h"

enum class ChatCodes;

class AbstractChatCmd : public QObject
{
    Q_OBJECT

public:
    static QHash<QString, User *> *getUsersListClient();
    static QHash<QString, User *> *getUsersListServer();
    static void setUsersListClient(QHash<QString, User *> *usersList);
    static void setUsersListServer(QHash<QString, User *> *usersList);

    AbstractChatCmd();

    virtual ~AbstractChatCmd(){}
    virtual void execute(ChatHeader &header, QString &arg) = 0;
    virtual QString getHelp() = 0;

private:
    static QHash<QString, User *> *s_UsersListClient;
    static QHash<QString, User *> *s_UsersListServer;

signals:
    void cmdSendPacketToAll(ChatCodes code, QString message);
    void cmdSendPacketToOne(ChatCodes code, QString message,
                                     QString receiverNickname);
    void cmdSendMessageToUI(const QString &msg);
};

#endif // ABSTRACTCHATCMD_H
