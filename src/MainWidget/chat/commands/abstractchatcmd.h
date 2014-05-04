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
    static void setListUsers(QHash<QString, User *> *listUsers);
    static QHash<QString, User *> *getListUsers();

    AbstractChatCmd();

    virtual ~AbstractChatCmd(){}
    virtual void execute(ChatHeader &header, QString &arg) = 0;
    virtual QString getHelp() = 0;

private:
    static QHash<QString, User *> *s_ListUsers;

signals:
    void cmdSendPacketToAll(ChatCodes code, QString message);
    void cmdSendPacketToOne(ChatCodes code, QString message,
                                     QString receiverNickname);
};

#endif // ABSTRACTCHATCMD_H
