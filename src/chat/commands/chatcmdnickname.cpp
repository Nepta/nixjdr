#include "chatcmdnickname.h"
#include "chatcmds.h"

ChatCmdNickname::ChatCmdNickname() {
}

void ChatCmdNickname::execute(ChatHeader &header, QString &arg) {
    // save the user and remove the old value from the hash
    QString oldNickname = header.getSocketUserNickname();
    User *user = AbstractChatCmd::getUsersListServer()->value(oldNickname);
    AbstractChatCmd::getUsersListServer()->remove(oldNickname);

    executeOnUser(user, arg, oldNickname, false);
}

void ChatCmdNickname::executeOnUser(User *user, QString askedNickname, QString oldNickname,
    bool isNew)
{
    QString checkedNickname = verifyAndGetNickname(askedNickname);

    if (isNew) {
        emit cmdSendPacketToAll(ChatCodes::SRVCMD_MESSAGE,
                                tr("<em>%1 vient de se connecter</em>").arg(checkedNickname));
    }

    /* update all the connected clients usersList (except the owner of the nickname being modified)
       with the following data : oldNickname, newNickname, isOwner (false) and isNew */
    emit cmdSendPacketToAll(ChatCodes::SRVCMD_NICK_ACK, QString("%1 %2 %3 %4")
                            .arg(oldNickname).arg(checkedNickname).arg(false).arg(isNew));

    // modify the user's nickname and add the new pair to the hash
    user->setNickname(checkedNickname);
    AbstractChatCmd::getUsersListServer()->insert(checkedNickname, user);

    // acknowledge : update the client (isOwner is true)
    emit cmdSendPacketToOne(ChatCodes::SRVCMD_NICK_ACK, QString("%1 %2 %3 %4")
                            .arg(oldNickname).arg(checkedNickname).arg(true).arg(isNew),
                            checkedNickname);
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
