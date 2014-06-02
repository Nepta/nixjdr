#include "ReceiverHandler.h"

ReceiverHandler::ReceiverHandler() {}
ReceiverHandler::~ReceiverHandler() {}

void ReceiverHandler::setupClientReceiver(ClientReceiver *clientReceiver) {
    m_ClientReceiver = clientReceiver;
}

void ReceiverHandler::setupServerReceiver(ServerReceiver *serverReceiver) {
    m_ServerReceiver = serverReceiver;
}
