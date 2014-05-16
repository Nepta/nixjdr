#ifndef ABSTRACTCHATCMD_H
#define ABSTRACTCHATCMD_H

#include <QObject>
#include <QString>
#include <QHash>
#include "Network/Header.h"
#include "Network/Switch.h"
#include "Network/NetworkCommon.h"
#include "chat/Message.h"
#include "User.h"

enum class ChatCodes : quint16;

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
    virtual void execute(Header &header, QString& arg) = 0;
    virtual QString getHelp() = 0;

private:
    static QHash<QString, User *> *s_UsersListClient;
    static QHash<QString, User *> *s_UsersListServer;

signals:
    void cmdSendPacketToAll(TargetCode target, ChatCodes code, Serializable& data);
    void cmdSendPacketToOne(TargetCode target, ChatCodes code, Serializable& data, QString receiverNickname);
    void cmdSendMessageToChatUi(const QString &msg);
    void cmdUpdateUserListView();
};

#endif // ABSTRACTCHATCMD_H
