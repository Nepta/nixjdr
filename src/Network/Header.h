#ifndef CHATHEADER_H
#define CHATHEADER_H

#include <QtGlobal>
#include <QString>

/**
 * @brief The Header holds information being sent in the header of a packet.
 */
class Header
{
public:
    /**
     * @brief ChatHeader Default constructor, initializes m_DataSize to 0, m_Code to an undefined
     * command and m_Target to an undefined target.
     */
    Header();
    ~Header();

    void reset();

    quint16 getDataSize();
    quint16 getTarget();
    quint16 getCode();
    QString getSocketUserNickname();

    Header *setDataSize(quint16 dataSize);
    Header *setTarget(quint16 target);
    Header *setCode(quint16 code);
    Header *setSocketUserNickname(QString socketUser);

private:
    /**
     * @brief m_DataSize Size of the data being sent (packet size - header size)
     */
    quint16 m_DataSize;

    /**
     * @brief m_Target Module (Receiver) to which the packet should be sent
     */
    quint16 m_Target;

    /**
     * @brief m_Code Code meant to be translated by the Receiver in order to launch the appropriate
     * action
     */
    quint16 m_Code;

    /**
     * @brief m_SocketUserNickName This attribute is set after a packet has been received in order
     * to retrieve easily who sent the packet.
     */
    QString m_SocketUserNickName;
};

#endif // CHATHEADER_H
