#ifndef SENDER_H
#define SENDER_H

#include <QObject>
#include <QByteArray>
#include <QHash>
#include <QString>

#include "User.h"

class Sender : public QObject
{
    Q_OBJECT

public:
    Sender(QHash<QString, User *> *usersList);
    ~Sender();

protected:
    QHash<QString, User *> *m_UsersList;

    QByteArray preparePacket(quint16 code, quint16 target, const QByteArray &data);
    void sendPacketToOne(User *user, const QByteArray& packet);
    void sendPacketToList(QList<User*> users, const QByteArray& packet);
};

#endif // SENDER_H
