#include "chat/commands/Commands.h"
#include "Switch.h"
#include "Header.h"

Header::Header()
{
    m_MsgSize = 0;
    m_Target = (quint16) TargetCode::UNDEFINED;
    m_Code = (quint16) ChatCodes::UNDEFINED;
}

quint16 Header::getMsgSize() {
    return m_MsgSize;
}

quint16 Header::getCode() {
    return m_Code;
}

QString Header::getSocketUserNickname() {
    return m_SocketUserNickName;
}

Header *Header::setMsgSize(quint16 msgSize) {
    m_MsgSize = msgSize;

    return this;
}

Header *Header::setCode(quint16 code) {
    m_Code = code;

    return this;
}

Header* Header::setSocketUserNickname(QString socketUserNickname) {
    m_SocketUserNickName = socketUserNickname;

    return this;
}
