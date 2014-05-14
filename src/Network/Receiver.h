#ifndef RECEIVER_H
#define RECEIVER_H

#include <QString>
#include "Header.h"

class Receiver{
public:
	Receiver();
    virtual void processNewMessage(Header header, QString message) = 0;
};

#endif // RECEIVER_H
