#include "CmdNicknameAck.h"
#include "Common.h"

CmdNicknameAck::CmdNicknameAck()
{
}

void CmdNicknameAck::execute(Header &, QString &arg) {
    QString temp = arg;

    QString oldNickname = Common::extractFirstWord(temp);
    QString newNickname = Common::extractFirstWord(temp);
    bool isOwner = (Common::extractFirstWord(temp) == "1" ? true : false);
    bool isNew = (temp == "1" ? true : false);

    QHash<QString, User *> *usersList = AbstractCmd::getUsersListClient();
    User* user = usersList->value(oldNickname);

    if (isOwner) {
        user->setNickname(newNickname);
        usersList->remove(oldNickname);
        usersList->insert(newNickname, user);

        emit cmdSendMessageToChatUi(tr("Vous avez changé votre pseudo en %1.")
                                .arg(newNickname));
    }
    else if (isNew) {
        usersList->insert(newNickname, NULL);
    }
    else {
        usersList->remove(oldNickname);
        usersList->insert(newNickname, user);

        emit cmdSendMessageToChatUi(tr("%1 a changé son pseudo en %2.")
                                .arg(oldNickname)
                                .arg(newNickname));
    }

    emit cmdUpdateUserListView();
}

QString CmdNicknameAck::getHelp() {
    return NULL;
}
