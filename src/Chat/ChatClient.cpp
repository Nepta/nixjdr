#include "Commands/AbstractCmd.h"
#include "Message.h"
#include "ChatClient.h"
#include "Common.h"

ChatClient::ChatClient(User *user, QHash<QString, User *> *usersList) :
    ClientReceiver(user, usersList)
{
    m_User = user;
    m_UsersList = usersList;

    AbstractCmd::setUsersListClient(m_UsersList);

    // init commands
    connect(&m_Commands, SIGNAL(cmdSendMessageToChatUi(QString)),
            this, SIGNAL(sendMessageToChatUi(QString)));
    connect(&m_Commands, SIGNAL(cmdSendMessageToServer(QString)),
            this, SLOT(sendMessageToServer(QString)));
}

ChatClient::~ChatClient() {
}

void ChatClient::processNewMessage(Header header, QByteArray& data) {
    ChatCodes code = (ChatCodes) header.getCode();
    Message message(data);

    m_Commands.getServerCommand(code)->execute(header, message.getString());
}

void ChatClient::sendMessageToServer(const QString &msg) {
    ChatCodes cmdCode = translateCommandToCode(msg);
    TargetCode target = TargetCode::CHAT_SERVER;
    Message strippedMsg(stripCommandFromMessage(msg));

    sendPacketToServer((quint16) cmdCode, (quint16) target, strippedMsg);
}

ChatCodes ChatClient::translateCommandToCode(const QString &msg) {
    QString cmd = msg.split(" ").at(0);

    if (!msg.startsWith("/")) {
        return ChatCodes::USERCMD_MESSAGE;
    }
    else {
        return Commands::s_CommandCodes.value(cmd, ChatCodes::USERCMD_HELP);
    }
}

QString ChatClient::stripCommandFromMessage(const QString &msg) {
    QString strippedMsg = msg;

    if (msg.startsWith("/")) {
        Common::extractFirstWord(strippedMsg);
        strippedMsg = strippedMsg.trimmed();
    }

    return strippedMsg;
}