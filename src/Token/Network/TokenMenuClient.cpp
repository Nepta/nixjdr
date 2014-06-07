#include "Database/Repository/RepositoryManager.h"
#include "Network/Serializable/Message.h"
#include "Network/Switch.h"
#include "TokenMenuCodes.h"
#include "TokenMenuClient.h"

TokenMenuClient::TokenMenuClient(User *user, QHash<QString, User *> *usersList,
    TokenMenu *tokenMenu) :
    SenderClient(user, usersList)
{
    m_TokenMenu = tokenMenu;
}

TokenMenuClient::~TokenMenuClient() {}

void TokenMenuClient::processNewData(Header header, QByteArray &data) {
    Message msg(data);
    TokenMenuCodes code = (TokenMenuCodes) header.getCode();

    if (code == TokenMenuCodes::ADD_TOKEN) {
        addTokenAction(msg.getString());
    }
}

void TokenMenuClient::sendMessageToServer(const QString& msg, quint16 code) {
    Message message(msg);
    TargetCode target = TargetCode::TOKEN_MENU_SERVER;

    sendPacketToServer(code, (quint16) target, message);
}

void TokenMenuClient::addTokenAction(const QString& msg) {
    int tokenId = msg.toInt();

    // Retrieve TokenItem from the token id
    TokenItem *tokenItem = RepositoryManager::s_TokenItemRepository.getTokenItemById(tokenId);

    // Add the TokenItem to the TokenList through the TokenMenu
    m_TokenMenu->addItem(tokenItem);
}
