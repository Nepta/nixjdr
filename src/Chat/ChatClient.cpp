#include "Network/Serializable/Message.h"
#include "Commands/AbstractCmd.h"
#include "ChatClient.h"
#include "Common.h"

ChatClient::ChatClient(User *user, QHash<QString, User *> *usersList) :
    SenderClient(user, usersList)
{
    AbstractCmd::setUsersListClient(m_UsersList);

    // init commands
    connect(&m_Commands, SIGNAL(cmdSendMessageToChatUi(QString)),
            this, SIGNAL(sendMessageToChatUi(QString)));
    connect(&m_Commands, SIGNAL(cmdSendMessageToServer(QString)),
            this, SLOT(sendMessageToServer(QString)));
}

ChatClient::~ChatClient() {
}

void ChatClient::processNewData(Header header, QByteArray& data) {
    ChatCodes code = (ChatCodes) header.getCode();
    Message message(data);

    m_Commands.getServerCommand(code)->execute(header, message.getString());
}

/**
 * @brief sendMessageToServer Sends a Message with the given code to the CHAT_SERVER. If the given
 * code is UNDEFINED, interprets the command given in msg to retrieve the code.
 * @param msg
 * @param code
 */
void ChatClient::sendMessageToServer(const QString& msg, quint16 code) {
    quint16 cmdCode;
    QString strippedMsg;
    if (code == (quint16) ChatCodes::UNDEFINED) {
        cmdCode = (quint16) translateCommandToCode(msg);
        strippedMsg = stripCommandFromMessage(msg);
    } else {
        cmdCode = code;
        strippedMsg = msg;
    }

    TargetCode target = TargetCode::CHAT_SERVER;
    Message message(strippedMsg);

    sendPacketToServer(cmdCode, (quint16) target, message);
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
