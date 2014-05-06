#include "chatcmdnickname.h"
#include "chatcmds.h"

ChatCmdNickname::ChatCmdNickname()
{
}

void ChatCmdNickname::execute(ChatHeader &header, QString &arg) {
    QString oldNickname;
    QString checkedNickname;
    User *tempUser;

    // save the user and remove the old value from the hash
    oldNickname = header.getSocketUserNickname();
    tempUser = AbstractChatCmd::getUsersListServer()->value(oldNickname);
    AbstractChatCmd::getUsersListServer()->remove(oldNickname);

    // new nickname
    checkedNickname = verifyAndGetNickname(arg);

    // modify the nickname in user, header and add the new pair to the hash
    tempUser->setNickname(checkedNickname);
    header.setSocketUserNickname(checkedNickname);
    AbstractChatCmd::getUsersListServer()->insert(checkedNickname, tempUser);

    // acknowledge
    emit cmdSendPacketToOne(ChatCodes::SRVCMD_NICK_ACK,
                            QString(oldNickname + " " + checkedNickname), checkedNickname);

    // TODO send updated list of users to all clients
}

void ChatCmdNickname::executeNewClientConnection(User *newUser) {
    QString oldNickname;
    QString checkedNickname;

    oldNickname = QString("guest");
    checkedNickname = verifyAndGetNickname(oldNickname);
    newUser->setNickname(checkedNickname);
    emit cmdSendPacketToAll(ChatCodes::SRVCMD_MESSAGE,
                            tr("<em>%1 vient de se connecter</em>").arg(checkedNickname));
    AbstractChatCmd::getUsersListServer()->insert(checkedNickname, newUser);

    // acknowledge
    emit cmdSendPacketToOne(ChatCodes::SRVCMD_NICK_ACK,
                            QString(oldNickname + " " + checkedNickname), checkedNickname);
}

QString ChatCmdNickname::getHelp() {
    return tr("/nickname pseudonyme - Permet de modifier votre pseudonyme.");
}

QString ChatCmdNickname::verifyAndGetNickname(QString nickname) {
    QString tempNickname = nickname;

    while (AbstractChatCmd::getUsersListServer()->contains(tempNickname)) {
        tempNickname += "_";
    }

    return tempNickname;
}
