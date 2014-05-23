#include "CmdHelp.h"

CmdHelp::CmdHelp(QHash<ChatCodes, AbstractCmd *> *commandsHash)
{
    m_CommandsHash = commandsHash;
}

void CmdHelp::execute(Header &header, QString &arg)
{
    QString helpString, user;

    user = header.getSocketUserNickname();

    QList<AbstractCmd*> commands = m_CommandsHash->values();

    helpString.append("Liste des commandes \n");
    foreach(AbstractCmd* cmd, commands) {
        if (cmd->getHelp() != NULL) {
            helpString.append(cmd->getHelp().append("\n"));
        }
    }

    Message helpMsg(helpString);

    emit cmdSendPacketToOne(
        TargetCode::CHAT_CLIENT,
        ChatCodes::SRVCMD_MESSAGE,
        helpMsg,
        user
    );
}

QString CmdHelp::getHelp(){
    return NULL;
}
