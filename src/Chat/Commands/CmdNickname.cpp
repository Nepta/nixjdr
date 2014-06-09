#include "CmdNickname.h"
#include "Commands.h"

CmdNickname::CmdNickname() {
}

void CmdNickname::execute(Header &header, QString &arg) {
    QString oldNickname = header.getSocketUserNickname();

    if (checkValidNickname(oldNickname, arg)) {
        // save the user and remove the old value from the hash
        User *user = AbstractCmd::getUsersListServer()->value(oldNickname);
        AbstractCmd::getUsersListServer()->remove(oldNickname);

        executeOnUser(user, arg, oldNickname, false);
    }
}

void CmdNickname::executeOnUser(User *user, QString askedNickname, QString oldNickname, bool isNew)
{
    QString checkedNickname = checkDuplicateNickname(askedNickname);

    if (isNew) {
        sendConnectionMessage(checkedNickname);
    }

    // Update all the connected clients usersList (except the owner of the nickname being modified).
    updateClientsUsersList(oldNickname, checkedNickname, false, isNew);

    // modify the user's nickname and add the new pair to the hash
    user->setNickname(checkedNickname);
    AbstractCmd::getUsersListServer()->insert(checkedNickname, user);

    // acknowledge : update the new user's client
    updateClientsUsersList(oldNickname, checkedNickname, true, isNew);

    if(checkedNickname.left(5) != "guest"){
        emit addPlayerToInterface(checkedNickname);
    }
}

void CmdNickname::sendConnectionMessage(QString nickname) {
    Message connectMessage(tr("<em>%1 vient de se connecter</em>").arg(nickname));
    emit cmdSendPacketToAll(
        TargetCode::CHAT_CLIENT,
        ChatCodes::SRVCMD_MESSAGE,
        connectMessage
    );
}

QString CmdNickname::getHelp() {
    return tr("/nickname pseudonyme - Permet de modifier votre pseudonyme.");
}

QString CmdNickname::checkDuplicateNickname(QString nickname) {
    QString tempNickname = nickname;

    while (AbstractCmd::getUsersListServer()->contains(tempNickname)) {
        tempNickname += "_";
    }

    return tempNickname;
}

bool CmdNickname::checkValidNickname(QString oldNickname, QString nickname) {
    if (nickname == "" || nickname.contains(" ")) {
        Message msg(tr("<em>Veuillez spécifier un pseudonyme valide (doit au moins contenir 1 "
                       "caractère et ne doit pas contenir d'espaces).</em>"));
        emit cmdSendPacketToOne(
            TargetCode::CHAT_CLIENT,
            ChatCodes::SRVCMD_MESSAGE,
            msg,
            oldNickname
        );

        return false;
    }

    return true;
}

void CmdNickname::updateClientsUsersList(QString oldNickname, QString checkedNickname, bool isOwner,
    bool isNew)
{
    Message msgUpdate(QString("%1 %2 %3 %4")
        .arg(oldNickname)
        .arg(checkedNickname)
        .arg(isOwner)
        .arg(isNew)
    );

    if (!isOwner) {
        emit cmdSendPacketToAll(
            TargetCode::CHAT_CLIENT,
            ChatCodes::SRVCMD_NICK_ACK,
            msgUpdate
        );
    }
    else {
        emit cmdSendPacketToOne(
            TargetCode::CHAT_CLIENT,
            ChatCodes::SRVCMD_NICK_ACK,
            msgUpdate,
            checkedNickname
        );
    }
}
