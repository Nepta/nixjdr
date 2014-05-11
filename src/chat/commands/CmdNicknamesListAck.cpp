#include "CmdNicknamesListAck.h"

CmdNicknamesListAck::CmdNicknamesListAck() {
}

void CmdNicknamesListAck::execute(ChatHeader &, QString &arg) {
    QHash<QString, User*> *userList = AbstractCmd::getUsersListClient();
    QStringList nicknamesList = arg.split(" ");

    // Retrieve the user associated with the current client
    User *user;
    foreach(User *userTemp, userList->values()) {
        if (userTemp != NULL) {
            user = userTemp;
        }
    }

    // Clear the current userList
    userList->clear();

    // Reconstruct userList
    foreach(QString nickname, nicknamesList) {
        if (nickname == user->getNickname()) {
            userList->insert(nickname, user);
        } else {
            userList->insert(nickname, NULL);
        }
    }

    // update the listView in the UI
    emit cmdUpdateUserListView();
}

QString CmdNicknamesListAck::getHelp() {
    return NULL;
}
