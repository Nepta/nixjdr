#include "chatcmdnickname.h"
#include "chatcmds.h"

ChatCmdNickname::ChatCmdNickname()
{
}

void ChatCmdNickname::execute(ChatHeader &header, QString &arg) {
    QString checkedNickname;
    User *tempUser;

    // save the user and remove the old value from the hash
    tempUser = AbstractChatCmd::getListUsers()->value(header.getSocketUserNickname());
    AbstractChatCmd::getListUsers()->remove(header.getSocketUserNickname());

    // new nickname
    checkedNickname = verifyAndGetNickname(arg);

    // modify the nickname in user, header and add the new pair to the hash
    tempUser->setNickname(checkedNickname);
    header.setSocketUserNickname(checkedNickname);
    AbstractChatCmd::getListUsers()->insert(checkedNickname, tempUser);

    // acknowledge
    emit cmdSendPacketToOne(ChatCodes::SRVCMD_NICK_ACK, checkedNickname, checkedNickname);

    // TODO send updated list of users to all clients
}

void ChatCmdNickname::executeNewClientConnection(User *newUser) {
    QString checkedNickname;

    checkedNickname = verifyAndGetNickname("guest");
    newUser->setNickname(checkedNickname);
    emit cmdSendPacketToAll(ChatCodes::SRVCMD_MESSAGE,
                            tr("<em>%1 vient de se connecter</em>").arg(checkedNickname));
    AbstractChatCmd::getListUsers()->insert(checkedNickname, newUser);
    emit cmdSendPacketToOne(ChatCodes::SRVCMD_NICK_ACK, checkedNickname, checkedNickname);
}

QString ChatCmdNickname::getHelp() {
    return tr("/nickname pseudonyme - Permet de modifier votre pseudonyme.");
}

QString ChatCmdNickname::verifyAndGetNickname(QString nickname) {
    QString tempNickname = nickname;

    while (AbstractChatCmd::getListUsers()->contains(tempNickname)) {
        tempNickname += "_";
    }

    return tempNickname;
}
