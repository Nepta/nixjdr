#ifndef TURNMENUCLIENT_H
#define TURNMENUCLIENT_H

#include "Network/SenderClient.h"
#include "Network/Receiver.h"
#include "TurnMenu/TurnMenu.h"

class TurnMenuClient : public SenderClient, public Receiver
{
    Q_OBJECT

public:
    TurnMenuClient(User *user, QHash<QString, User *> *usersList, TurnMenu *turnMenu);
    ~TurnMenuClient();

    void processNewData(Header header, QByteArray &data);

public slots:
    void sendMessageToServer(const QString& msg, quint16 code);

private:
    TurnMenu *m_TurnMenu;

    void updateTurnAction(const QString& msg);
};

#endif // TURNMENUCLIENT_H
