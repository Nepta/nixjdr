#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QString>
#include "Header.h"

class Receiver : public QObject {
    Q_OBJECT
public:
    Receiver(){}

protected slots:
    virtual void processNewMessage(Header header, QString message) = 0;
};

#endif // RECEIVER_H
