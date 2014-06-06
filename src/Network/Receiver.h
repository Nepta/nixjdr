#ifndef RECEIVER_H
#define RECEIVER_H

#include <QString>
#include "Header.h"
#include "User.h"

class Receiver
{
	 bool isLoggable_;

public:
    static const quint16 UNDEFINED_CODE = 0;
	 virtual ~Receiver();
	 bool isLoggable();

    /**
     * @brief processNewData Interprets incoming data from a packet
     * @param header packet's header
     * @param data data to process
     */
    virtual void processNewData(Header header, QByteArray& data) = 0;

protected:
	 void isLoggable(bool newStatus);
};

#endif // RECEIVER_H
