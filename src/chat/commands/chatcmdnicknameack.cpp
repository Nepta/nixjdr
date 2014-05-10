#include "chatcmdnicknameack.h"
#include "chat/chatcommon.h"

ChatCmdNicknameAck::ChatCmdNicknameAck()
{
}

void ChatCmdNicknameAck::execute(ChatHeader &, QString &arg) {
    QString temp = arg;

    QString oldNickname = ChatCommon::extractFirstWord(temp);
    QString newNickname = ChatCommon::extractFirstWord(temp);
    bool isOwner = (ChatCommon::extractFirstWord(temp) == "1" ? true : false);
    bool isNew = (temp == "1" ? true : false);

    QHash<QString, User *> *usersList = AbstractChatCmd::getUsersListClient();
    User* user = usersList->value(oldNickname);

    if (isOwner) {
        user->setNickname(newNickname);
        usersList->remove(oldNickname);
        usersList->insert(newNickname, user);

        emit cmdSendMessageToUI(tr("Vous avez changé votre pseudo en %1.")
                                .arg(newNickname));
    }
    else if (isNew) {
        usersList->insert(newNickname, NULL);
    }
    else {
        usersList->remove(oldNickname);
        usersList->insert(newNickname, user);

        emit cmdSendMessageToUI(tr("%1 a changé son pseudo en %2.")
                                .arg(oldNickname)
                                .arg(newNickname));
    }

    emit cmdUpdateUserListView();
}

QString ChatCmdNicknameAck::getHelp() {
    return NULL;
}
