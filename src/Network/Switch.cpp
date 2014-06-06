#include "Switch.h"

Receiver *Switch::getReceiver(TargetCode code) {
    return m_Nodes.value(code);
}

Receiver *Switch::switchNewMessage(Header header, QByteArray message) {
	quint16 target = header.getTarget();

	Receiver *receiver = m_Nodes.value((TargetCode) target);
	receiver->processNewData(header, message);
	return receiver;
}
