#include "SenderHandler.h"

SenderHandler::SenderHandler() {}
SenderHandler::~SenderHandler() {}

void SenderHandler::setSenderClient(SenderClient *senderClient) {
    m_SenderClient = senderClient;
}

void SenderHandler::setSenderServer(SenderServer *senderServer) {
    m_SenderServer = senderServer;
}
