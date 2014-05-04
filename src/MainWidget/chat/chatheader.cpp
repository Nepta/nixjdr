#include "chatheader.h"
#include "chatcommon.h"

ChatHeader::ChatHeader()
{
    m_MsgSize = 0;
    m_Cmd = ChatCommon::UNDEFINED;
}

ChatHeader::ChatHeader(quint16 msgSize, quint16 cmd)
{
    m_MsgSize = msgSize;
    m_Cmd = cmd;
}

quint16 ChatHeader::getMsgSize() {
    return m_MsgSize;
}

quint16 ChatHeader::getCmd() {
    return m_Cmd;
}

QString ChatHeader::getSocketUserNickname() {
    return m_SocketUserNickName;
}

ChatHeader *ChatHeader::setMsgSize(quint16 msgSize) {
    m_MsgSize = msgSize;

    return this;
}

ChatHeader *ChatHeader::setCmd(quint16 cmd) {
    m_Cmd = cmd;

    return this;
}

ChatHeader* ChatHeader::setSocketUserNickname(QString socketUserNickname) {
    m_SocketUserNickName = socketUserNickname;

    return this;
}

