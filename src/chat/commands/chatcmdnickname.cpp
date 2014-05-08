#include "chatcmdnickname.h"
#include "chatcmds.h"

ChatCmdNickname::ChatCmdNickname() {
}

// TODO REFACTO (CODE DUPLICATION)
void ChatCmdNickname::execute(ChatHeader &header, QString &arg) {
    User *tempUser;
    QString oldNickname, checkedNickname;
    bool isNew = false;

    // save the user and remove the old value from the hash
    oldNickname = header.getSocketUserNickname();
    tempUser = AbstractChatCmd::getUsersListServer()->value(oldNickname);
    AbstractChatCmd::getUsersListServer()->remove(oldNickname);

    // new nickname
    checkedNickname = verifyAndGetNickname(arg);

    /* update all the connected clients usersList (except the one who changed his nickname)
       with the following data : oldNickname, newNickname, isOwner (false) and isNew (false)*/
    emit cmdSendPacketToAll(ChatCodes::SRVCMD_NICK_ACK, QString("%1 %2 %3 %4")
                            .arg(oldNickname).arg(checkedNickname).arg(false).arg(isNew));

    // modify the nickname in user, header and add the new pair to the hash
    tempUser->setNickname(checkedNickname);
    header.setSocketUserNickname(checkedNickname);
    AbstractChatCmd::getUsersListServer()->insert(checkedNickname, tempUser);

    // acknowledge : update the client who changed his username (isOwner is true)
    emit cmdSendPacketToOne(ChatCodes::SRVCMD_NICK_ACK, QString("%1 %2 %3 %4")
                            .arg(oldNickname).arg(checkedNickname).arg(true).arg(isNew),
                            checkedNickname);
}

void ChatCmdNickname::executeNewClientConnection(User *newUser) {
    QString oldNickname;
    QString checkedNickname;
    bool isNew = true;

    oldNickname = QString("guest");
    checkedNickname = verifyAndGetNickname(oldNickname);

    emit cmdSendPacketToAll(ChatCodes::SRVCMD_MESSAGE,
                            tr("<em>%1 vient de se connecter</em>").arg(checkedNickname));

    /* update all the connected clients usersList (except the new one)
       with the following data : oldNickname, newNickname, isOwner (false) and isNew (true)*/
    emit cmdSendPacketToAll(ChatCodes::SRVCMD_NICK_ACK, QString("%1 %2 %3 %4")
                            .arg(oldNickname).arg(checkedNickname).arg(false).arg(isNew));

    // modify the nickname for the new user and add the new pair to the hash
    newUser->setNickname(checkedNickname);
    AbstractChatCmd::getUsersListServer()->insert(checkedNickname, newUser);

    // acknowledge : update the new client (isOwner is true)
    emit cmdSendPacketToOne(ChatCodes::SRVCMD_NICK_ACK, QString("%1 %2 %3 %4")
                            .arg(oldNickname).arg(checkedNickname).arg(true).arg(isNew),
                            checkedNickname);

}
// END TODO REFACTO (CODE DUPLICATION)

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
