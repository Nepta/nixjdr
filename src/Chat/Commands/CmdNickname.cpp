#include "CmdNickname.h"
#include "Commands.h"

CmdNickname::CmdNickname() {
}

void CmdNickname::execute(Header &header, QString &arg) {
    QString oldNickname = header.getSocketUserNickname();

    if (arg != "") {
        // save the user and remove the old value from the hash
        User *user = AbstractCmd::getUsersListServer()->value(oldNickname);
        AbstractCmd::getUsersListServer()->remove(oldNickname);

        executeOnUser(user, arg, oldNickname, false);
    }
    else {
        Message msg(tr("<em>Veuillez spécifier un pseudonyme</em>"));
        emit cmdSendPacketToOne(TargetCode::CHAT_CLIENT, ChatCodes::SRVCMD_MESSAGE, msg, oldNickname);
    }
}

void CmdNickname::executeOnUser(User *user, QString askedNickname, QString oldNickname,
    bool isNew)
{
    QString checkedNickname = verifyAndGetNickname(askedNickname);

    if (isNew) {
        Message connectMessage(tr("<em>%1 vient de se connecter</em>").arg(checkedNickname));
        emit cmdSendPacketToAll(
            TargetCode::CHAT_CLIENT,
            ChatCodes::SRVCMD_MESSAGE,
            connectMessage
        );
    }

    /* update all the connected clients usersList (except the owner of the nickname being modified)
       with the following data : oldNickname, newNickname, isOwner (false) and isNew */
    Message msgUpdateList(QString("%1 %2 %3 %4")
        .arg(oldNickname)
        .arg(checkedNickname)
        .arg(false)
        .arg(isNew)
    );
    emit cmdSendPacketToAll(
        TargetCode::CHAT_CLIENT,
        ChatCodes::SRVCMD_NICK_ACK,
        msgUpdateList
    );

    // modify the user's nickname and add the new pair to the hash
    user->setNickname(checkedNickname);
    AbstractCmd::getUsersListServer()->insert(checkedNickname, user);

    // acknowledge : update the client (isOwner is true)
    Message msgUpdateClient = Message(QString("%1 %2 %3 %4")
        .arg(oldNickname)
        .arg(checkedNickname)
        .arg(true)
        .arg(isNew)
    );
    emit cmdSendPacketToOne(
        TargetCode::CHAT_CLIENT,
        ChatCodes::SRVCMD_NICK_ACK,
        msgUpdateClient,
        checkedNickname
    );
}

QString CmdNickname::getHelp() {
    return tr("/nickname pseudonyme - Permet de modifier votre pseudonyme.");
}

QString CmdNickname::verifyAndGetNickname(QString nickname) {
    QString tempNickname = nickname;

    while (AbstractCmd::getUsersListServer()->contains(tempNickname)) {
        tempNickname += "_";
    }

    return tempNickname;
}
