#include "chat/commands/Commands.h"
#include "Switch.h"
#include "Header.h"

Header::Header()
{
    m_DataSize = 0;
    m_Target = (quint16) TargetCode::UNDEFINED;
    m_Code = (quint16) ChatCodes::UNDEFINED;
}

Header::~Header() {
}

quint16 Header::getDataSize() {
    return m_DataSize;
}

quint16 Header::getTarget() {
    return m_Target;
}

quint16 Header::getCode() {
    return m_Code;
}

QString Header::getSocketUserNickname() {
    return m_SocketUserNickName;
}

Header *Header::setDataSize(quint16 dataSize) {
    m_DataSize = dataSize;

    return this;
}

Header *Header::setTarget(quint16 target) {
    m_Target = target;

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
