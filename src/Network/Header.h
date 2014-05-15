#ifndef CHATHEADER_H
#define CHATHEADER_H

#include <QtGlobal>
#include <QString>

class Header
{
public:
    /**
     * @brief ChatHeader Default constructor, initializes m_MsgSize to 0 and m_Cmd to an undefined command
     */
    Header();

    /**
     * @brief getMsgSize    Returns the message's size
     * @return  m_MsgSize
     */
    quint16 getMsgSize();

    quint16 getTarget();

    /**
     * @brief getCmd    Returns the message's command's code
     * @return  m_Cmd
     */
    quint16 getCode();

    /**
     * @brief getSocketUserNickname     Returns the socket's sender's nickname
     * @return  m_SocketUserNickName
     */
    QString getSocketUserNickname();

    /**
     * @brief setMsgSize    Sets the message's size to the specified value
     * @param msgSize   New message size
     * @return  A pointer towards the current header
     */
    Header *setMsgSize(quint16 msgSize);

    Header *setTarget(quint16 target);

    /**
     * @brief setCode    Sets the message's code to the specified value
     * @param code   New code
     * @return  A pointer towards the current header
     */
    Header *setCode(quint16 code);

    /**
    * @brief setSocketUserNickname     Sets the socket's user to the specified value
    * @param socketUser    New socket's user
    * @return A pointer towards the current header
    */
    Header *setSocketUserNickname(QString socketUser);

private:
    /**
     * @brief m_MsgSize Message size (= packet size - header size)
     */
    quint16 m_MsgSize;

    /**
     * @brief m_Target Module (Receiver) to which the packet should be sent
     */
    quint16 m_Target;

    /**
     * @brief m_Code Code meant to be translated by the Receiver in order to launch the appropriate
     * action
     */
    quint16 m_Code;

    QString m_SocketUserNickName;
};

#endif // CHATHEADER_H
