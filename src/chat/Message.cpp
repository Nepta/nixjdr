#include <QDataStream>
#include "Message.h"

Message::Message(const QString &msg)
{
    m_Msg = msg;
}

Message::Message(QByteArray& data) {
    unserialize(data);
}

QByteArray Message::serialize() {
    QByteArray serializedData;
    QDataStream stream(&serializedData, QIODevice::WriteOnly);

    stream << m_Msg;

    return serializedData;
}

void Message::unserialize(QByteArray& data) {
    QDataStream stream(&data, QIODevice::ReadOnly);

    stream >> m_Msg;
}

QString &Message::getString() {
    return m_Msg;
}
