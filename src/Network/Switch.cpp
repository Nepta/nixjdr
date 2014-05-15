#include "Switch.h"

Receiver *Switch::getReceiver(TargetCode code) {
    return m_Nodes.value(code);
}

void Switch::switchNewMessage(Header header, QString message) {
    quint16 target = header.getTarget();

    Receiver *receiver = m_Nodes.value((TargetCode) target);
    receiver->processNewMessage(header, message);
}
