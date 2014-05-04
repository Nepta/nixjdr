#include "chatserver.h"
#include<QTranslator>

ChatServer::ChatServer()
{
    server = new QTcpServer(this);
}

ChatServer::~ChatServer()
{
    server->deleteLater();
    qDeleteAll(listUsers.begin(), listUsers.end());
    listUsers.clear();
}

void ChatServer::init() {
    //if (!server->listen(QHostAddress::Any)) {
    //TEST
    if (!server->listen(QHostAddress::Any, 50885)) {
    //TEST
        QString msg = tr("Le server n'a pas pu être démarré. Raison :<br />") + server->errorString();
        emit sendMessageToUI(msg);
    }
    else {
        QString msg = tr("Le server a été démarré sur le port <strong>")
                + QString::number(server->serverPort())
                + tr("</strong>.<br />Des clients peuvent maintenant se connecter.");
        emit sendMessageToUI(msg);

        connect(server, SIGNAL(newConnection()), this, SLOT(newClientConnection()));
    }
}

/**
 * @brief ChatServer::newClientConnection
 */
void ChatServer::newClientConnection()
{
    QString checkedNickname;

    sendPacketToAll(ChatCommon::MESSAGE,
                    tr("<em>Un nouveau client vient de se connecter</em>"));

    //QTcpSocket *newUserSocket = server->nextPendingConnection();
    User *newUser = new User(server->nextPendingConnection());

    checkedNickname = verifyAndGetNickname("guest");
    newUser->setNickname(checkedNickname);
    listUsers.insert(checkedNickname, newUser);
    sendPacketToOne(ChatCommon::SRVCMD_NICK_ACK, checkedNickname, checkedNickname);

    // full packet has been received -> process and send it
    connect(newUser, SIGNAL(receivedFullData(ChatHeader, QString)),
            this, SLOT(processNewMessage(ChatHeader, QString)));
    connect(newUser, SIGNAL(userDisconnectedNotify(User&)), this, SLOT(userDisconnected(User&)));
}

void ChatServer::userDisconnected(User &user)
{
    sendPacketToAll(ChatCommon::MESSAGE,
                    user.getNickname() + tr(" <em>vient de se déconnecter</em>"));

    listUsers.remove(user.getNickname());

    // The socket may still be in use even though the client is disconnected (e.g.
    // message still being sent).
    user.deleteLater();
}

/**
 * @brief ChatServer::processNewMessage
 * @param header
 * @param message
 */
void ChatServer::processNewMessage(ChatHeader header, QString message) {
    switch (header.getCmd()) {
        case ChatCommon::MESSAGE :
            sendMessageToAll(header, message);
            break;

        case ChatCommon::USERCMD_NICK :
            cmdModifyNickname(header, message);
            break;

        case ChatCommon::USERCMD_WHISP :
            cmdWhisp(header, message);
            break;
    }
}

void ChatServer::sendPacketToAll(ChatCommon::commands code, QString message)
{
    QByteArray packet;
    packet = ChatCommon::preparePacket(code, message);

    for (int i = 0; i < listUsers.values().size(); i++)
    {
        listUsers.values()[i]->getSocket()->write(packet);
    }
}

void ChatServer::sendPacketToOne(ChatCommon::commands code, QString message,
                                 QString receiverNickname) {
    QByteArray packet;

    packet = ChatCommon::preparePacket(code, message);
    listUsers.value(receiverNickname)->getSocket()->write(packet);
}

void ChatServer::sendMessageToAll(ChatHeader &header, QString &message) {
        QString namedMessage = QString("[%1]: %2")
                           .arg(header.getSocketUserNickname())
                           .arg(message);

    sendPacketToAll(ChatCommon::MESSAGE, namedMessage);
}

quint16 ChatServer::getPort()
{
    return server->serverPort();
}

QString ChatServer::verifyAndGetNickname(QString nickname) {
    QString tempNickname = nickname;

    while (listUsers.contains(tempNickname)) {
        tempNickname += "_";
    }

    return tempNickname;
}

void ChatServer::cmdModifyNickname(ChatHeader &header, QString nickname) {
    QString checkedNickname;
    User *tempUser;

    // save the user and remove the old value from the hash
    tempUser = listUsers.value(header.getSocketUserNickname());
    listUsers.remove(header.getSocketUserNickname());

    // new nickname
    checkedNickname = verifyAndGetNickname(nickname);

    // modify the nickname in user, header and add the new pair to the hash
    tempUser->setNickname(checkedNickname);
    header.setSocketUserNickname(checkedNickname);
    listUsers.insert(checkedNickname, tempUser);

    // acknowledge
    sendPacketToOne(ChatCommon::SRVCMD_NICK_ACK, checkedNickname, checkedNickname);

    // TODO send updated list of users to all clients
}

void ChatServer::cmdWhisp(ChatHeader &header, QString message) {
    QString strippedMsg, msgSender, msgTarget,
            sender, target;

    strippedMsg = message;
    sender = header.getSocketUserNickname();
    target = ChatCommon::extractFirstWord(strippedMsg);

    if (listUsers.contains(target)) {
        msgTarget = tr("[%1] chuchote: %2")
                .arg(sender)
                .arg(strippedMsg);

        msgSender = tr("à [%1]: %2")
                .arg(target)
                .arg(strippedMsg);

        sendPacketToOne(ChatCommon::SRVCMD_WHISP_REP, msgTarget, target);
        sendPacketToOne(ChatCommon::SRVCMD_WHISP_REP, msgSender, sender);
    }
    else {
        sendPacketToOne(ChatCommon::MESSAGE, target + tr(" n'existe pas."), sender);
    }

}
