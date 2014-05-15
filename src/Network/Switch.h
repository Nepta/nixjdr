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

/*private:
    QHash<TargetCode, Receiver*> m_Nodes;*/

public:
    Switch() {}
    virtual ~Switch() {}

    Receiver *getReceiver(TargetCode code);

protected:
    QHash<TargetCode, Receiver*> m_Nodes;

protected slots:
	/**
     * @brief redirect A message received by socket to right module
     * @param header   A header containing especially a target
     * @param message  The message to send
	 */
    void switchNewMessage(Header header, QString message);
};

#endif // SWITCH_H
