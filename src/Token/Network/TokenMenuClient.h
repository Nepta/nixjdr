#ifndef TOKENMENUCLIENT_H
#define TOKENMENUCLIENT_H

#include "Network/SenderClient.h"
#include "Network/Receiver.h"
#include "Token/TokenMenu.h"

class TokenMenuClient  : public SenderClient, public Receiver
{
public:
    TokenMenuClient(User *user, QHash<QString, User *> *usersList, TokenMenu *tokenMenu);
    ~TokenMenuClient();

    void processNewData(Header header, QByteArray &data);

public slots:
    void sendMessageToServer(const QString& msg, quint16 code);

private:
    TokenMenu *m_TokenMenu;

    void addTokenAction(const QString& msg);
    void updateTokenAction(const QString& msg);
};

#endif // TOKENMENUCLIENT_H
