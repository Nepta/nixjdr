#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QString>
#include "Header.h"
#include "User.h"

class Receiver : public QObject {
    Q_OBJECT
public:
    Receiver(QHash<QString, User *> *usersList);
    virtual ~Receiver(){}

protected:
    QHash<QString, User *> *m_UsersList;

public slots:
    virtual void processNewMessage(Header header, QString message) = 0;
};

#endif // RECEIVER_H
