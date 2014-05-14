#include "CmdConnectionAck.h"

CmdConnectionAck::CmdConnectionAck()
{
}

void CmdConnectionAck::execute(ChatHeader &header, QString &) {
    // Retrieve the user associated with the client
    User *user = AbstractCmd::getUsersListClient()->value(header.getSocketUserNickname());

    // Modify the temp nickname by the one asked by the user
    emit cmdSendMessageToServer(QString("/nickname %1").arg(user->getPendingNickname()));
}

QString CmdConnectionAck::getHelp() {
    return NULL;
}
