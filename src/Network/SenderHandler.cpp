#include "SenderHandler.h"

SenderHandler::SenderHandler() {}
SenderHandler::~SenderHandler() {}

void SenderHandler::setupSenderClient(SenderClient *senderClient) {
    m_SenderClient = senderClient;
}

void SenderHandler::setupSenderServer(SenderServer *senderServer) {
    m_SenderServer = senderServer;
}
