#include "CmdDisconnect.h"

CmdDisconnect::CmdDisconnect()
{
}

void CmdDisconnect::execute(Header &, QString &arg) {
    AbstractCmd::getUsersListClient()->remove(arg);

    emit cmdSendMessageToChatUi(tr("<strong>%1</strong><em> vient de se déconnecter</em>")
                            .arg(arg));

    // update the listView in the UI
    emit cmdUpdateUserListView();
}

QString CmdDisconnect::getHelp() {
    return NULL;
}
