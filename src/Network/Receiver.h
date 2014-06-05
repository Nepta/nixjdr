#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QString>
#include "Serializable.h"
#include "Header.h"
#include "User.h"

class Receiver : public QObject {
    Q_OBJECT
public:
    static const quint16 UNDEFINED_CODE = 0;

    Receiver(QHash<QString, User *> *usersList);
    virtual ~Receiver(){}
	 bool isLoggable();

protected:
    /**
     * @brief preparePacket Prepare a packet containing a header and the object to send.
     * @param code specifies which action should be executed when the packet is received
     * @param target specifies to which Receiver the packet should be redirected when received
     * @param data content of the packet
     * @return a packet
     */
    QByteArray preparePacket(quint16 code, quint16 target, const QByteArray &data);

    QHash<QString, User *> *m_UsersList;

	 void isLoggable(bool newStatus);

public slots:
    virtual void processNewMessage(Header header, QByteArray& data) = 0;

private:
	 bool m_isLoggable;
};

#endif // RECEIVER_H
