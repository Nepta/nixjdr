#ifndef CHATHEADER_H
#define CHATHEADER_H

#include <QtGlobal>
#include <QString>

class ChatHeader
{
public:
    /**
     * @brief ChatHeader Default constructor, initializes m_MsgSize to 0 and m_Cmd to an undefined command
     */
    ChatHeader();

    /**
     * @brief ChatHeader Initializes m_MsgSize and m_cmd with the specified parameters
     * @param msgSize   Size of the message
     * @param cmd       Command's code
     */
    ChatHeader(quint16 msgSize, quint16 cmd);

    /**
     * @brief getMsgSize    Returns the message's size
     * @return  m_MsgSize
     */
    quint16 getMsgSize();

    /**
     * @brief getCmd    Returns the message's command's code
     * @return  m_Cmd
     */
    quint16 getCmd();

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
    ChatHeader *setMsgSize(quint16 msgSize);

    /**
     * @brief setCmd    Sets the message's command's code to the specified value
     * @param cmd   New command code
     * @return  A pointer towards the current header
     */
    ChatHeader *setCmd(quint16 cmd);

    /**
     * @brief setSocketUserNickname     Sets the socket's user to the specified value
     * @param socketUser    New socket's user
     * @return A pointer towards the current header
     */
    ChatHeader *setSocketUserNickname(QString socketUser);

private:
    quint16 m_MsgSize;
    quint16 m_Cmd;
    QString m_SocketUserNickName;
};

#endif // CHATHEADER_H
