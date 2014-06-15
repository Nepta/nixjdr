#ifndef SWITCH_H
#define SWITCH_H

#include <QHash>
#include <QString>
#include <QObject>

#include "Serializable/Serializable.h"
#include "Header.h"
#include "Receiver.h"

enum class TargetCode {
    MAP_SERVER = 0,
    MAP_CLIENT,

    CHAT_SERVER,
    CHAT_CLIENT,

    TOKEN_MENU_SERVER,
    TOKEN_MENU_CLIENT,

    TURN_MENU_SERVER,
    TURN_MENU_CLIENT,

    UNDEFINED
};
inline uint qHash(const TargetCode &key) { return qHash((quint16) key); }

class Switch : public QObject {
    Q_OBJECT

public:
    Switch() {}
    virtual ~Switch() {}

    Receiver *getReceiver(TargetCode code);
	 void insert(TargetCode code, Receiver *receiver);

protected:
    QHash<TargetCode, Receiver*> m_Nodes;

protected slots:
	/**
     * @brief redirect A message received by socket to right module
     * @param header   A header containing especially a target
     * @param message  The message to send
	 */
	 Receiver* switchNewMessage(Header header, QByteArray message);
};

#endif // SWITCH_H
