#include "commands/AbstractCmd.h"
#include "ChatClient.h"
#include "ChatCommon.h"

ChatClient::ChatClient(User *user, QHash<QString, User *> *usersList) :
    ClientReceiver(user, usersList)
{
    m_User = user;
    m_UsersList = usersList;

    // init commands
    AbstractCmd::setUsersListClient(m_UsersList);
    connect(&m_Commands, SIGNAL(cmdSendMessageToChatUi(QString)),
            this, SIGNAL(sendMessageToChatUi(QString)));
}

ChatClient::~ChatClient() {
}

void ChatClient::processNewMessage(Header header, QString message) {
    ChatCodes code = (ChatCodes) header.getCode();

    m_Commands.getServerCommand(code)->execute(header, message);
}

void ChatClient::sendMessageToServer(const QString &msg) {
    ChatCodes cmdCode = translateCommandToCode(msg);
    TargetCode target = TargetCode::CHAT_SERVER;
    QString strippedMsg = stripCommandFromMessage(msg);

    sendPacketToServer((quint16) cmdCode, (quint16) target, strippedMsg);
}

ChatCodes ChatClient::translateCommandToCode(const QString &msg) {
    QString cmd = msg.split(" ").at(0);

    if (!msg.startsWith("/")) {
        return ChatCodes::USERCMD_MESSAGE;
    }
    else {
        // TODO remplacer par HELP
        return Commands::s_CommandCodes.value(cmd, ChatCodes::USERCMD_MESSAGE);
    }
}

QString ChatClient::stripCommandFromMessage(const QString &msg) {
    QString strippedMsg = msg;

    if (msg.startsWith("/")) {
        ChatCommon::extractFirstWord(strippedMsg);
        strippedMsg = strippedMsg.trimmed();
    }

    return strippedMsg;
}
