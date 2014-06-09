#include "Network/Serializable/Message.h"
#include "Network/Switch.h"
#include "TurnMenuClient.h"
#include "TurnMenuCodes.h"

TurnMenuClient::TurnMenuClient(User *user, QHash<QString, User *> *usersList, TurnMenu *turnMenu) :
    SenderClient(user, usersList)
{
    m_TurnMenu = turnMenu;
}

TurnMenuClient::~TurnMenuClient() {}

void TurnMenuClient::processNewData(Header header, QByteArray &data) {
    Message msg(data);
    TurnMenuCodes code = (TurnMenuCodes) header.getCode();

    if (code == TurnMenuCodes::ADD_TURN) {
        // TODO
    }
    else if (code == TurnMenuCodes::REMOVE_TURN) {
        // TODO
    }
}

void TurnMenuClient::sendMessageToServer(const QString& msg, quint16 code) {
    Message message(msg);
    TargetCode target = TargetCode::TURN_MENU_SERVER;

    sendPacketToServer(code, (quint16) target, message);
}
