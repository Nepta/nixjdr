#ifndef ABSTRACTCHATCMD_H
#define ABSTRACTCHATCMD_H

#include <QObject>
#include <QString>
#include <QHash>
#include "Network/Header.h"
#include "User.h"

enum class ChatCodes;

class AbstractCmd : public QObject
{
    Q_OBJECT

public:
    static QHash<QString, User *> *getUsersListClient();
    static QHash<QString, User *> *getUsersListServer();
    static void setUsersListClient(QHash<QString, User *> *usersList);
    static void setUsersListServer(QHash<QString, User *> *usersList);

    AbstractCmd();

    virtual ~AbstractCmd(){}
    virtual void execute(Header &header, QString &arg) = 0;
    virtual QString getHelp() = 0;

private:
    static QHash<QString, User *> *s_UsersListClient;
    static QHash<QString, User *> *s_UsersListServer;

signals:
    void cmdSendPacketToAll(ChatCodes code, QString message);
    void cmdSendPacketToOne(ChatCodes code, QString message,
                                     QString receiverNickname);
    void cmdSendMessageToChatUi(const QString &msg);
    void cmdUpdateUserListView();
};

#endif // ABSTRACTCHATCMD_H
