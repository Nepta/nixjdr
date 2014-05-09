#include "chatcmddisconnect.h"

ChatCmdDisconnect::ChatCmdDisconnect()
{
}

void ChatCmdDisconnect::execute(ChatHeader &header, QString &arg) {
    AbstractChatCmd::getUsersListClient()->remove(arg);

    emit cmdSendMessageToUI(tr("<strong>%1</strong><em> vient de se déconnecter</em>")
                            .arg(arg));

    // update the listView in the UI
    emit cmdUpdateUserListView();
}

QString ChatCmdDisconnect::getHelp() {
    return NULL;
}
