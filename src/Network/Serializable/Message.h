#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>

#include "Serializable.h"

class Message : public Serializable
{
public:
    Message(const QString &msg);
    Message(QByteArray& data);
    QByteArray serialize();
    QString& getString();

private:
    void unserialize(QByteArray& data);
    QString m_Msg;
};

#endif // MESSAGE_H
