#ifndef NETWORKCOMMON_H
#define NETWORKCOMMON_H

#include <QTcpSocket>
#include <QByteArray>
#include <QObject>
#include "Network/Header.h"

/**
 * @brief The NetworkCommon class holds general processing functions concerning packets (preparation
 * and reception).
 */
class NetworkCommon
{
public:
    NetworkCommon(){}

    /**
     * @brief preparePacket Prepare a packet containing a header and the object to send.
     * @param code specifies which action should be executed when the packet is received
     * @param target specifies to which Receiver the packet should be redirected when received
     * @param data content of the packet
     * @return a packet
     */
    static QByteArray preparePacket(quint16 code, quint16 target, const QByteArray &data);

    /**
     * @brief packetReadyToReceive Returns if the packet has been fully received, and fill the
     * header and the object.
     * @param socket Socket receiving a packet
     * @param header Header to fill
     * @param data data to fill
     * @return packet reception state (true: fully received, false: being received)
     */
    static bool packetReadyToReceive(QTcpSocket *socket, Header &header, QByteArray &data);
};

#endif // NETWORKCOMMON_H
