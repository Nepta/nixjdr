#ifndef SWITCH_H
#define SWITCH_H

#include <QHash>
#include <QString>
#include <QObject>
#include "Header.h"
#include "Receiver.h"

enum class TargetCode {
    MAP_SERVER = 0,
    MAP_CLIENT,

    CHAT_SERVER,
    CHAT_CLIENT,

    UNDEFINED
};
inline uint qHash(const TargetCode &key) { return qHash((quint16) key); }

class Switch : public QObject {
    Q_OBJECT

private:
    QHash<TargetCode, Receiver*> m_Nodes;

public:
	Switch();

    /**
     * @brief addNode add a possible target
     * @param receiver the target to Add
     */
    Switch& addNode(TargetCode targetCode, Receiver *receiver);

public slots:
	/**
	 * @brief redirect a message received by socket to right module
	 * @param header a header containing especially a target
	 * @param message the message to send
	 */
    void switchNewMessage(Header &header, QString &message);
};

#endif // SWITCH_H
