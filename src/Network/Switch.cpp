#include "Switch.h"

Switch::Switch(){
}

Switch& Switch::addNode(TargetCode targetCode, Receiver *receiver){
    m_Nodes.insert(targetCode, receiver);

    return *this;
}

void Switch::switchNewMessage(Header &header, QString &message) {
    // TODO
}
