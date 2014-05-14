#ifndef SWITCH_H
#define SWITCH_H

#include <QHash>
#include <QString>
#include "../chat/ChatHeader.h"
#include "Receiver.h"


enum class TargetCode{
	MAP = 0,
	CHAT
};

class Switch{
	QHash<TargetCode,Receiver&> nodes;

private:
	/**
	 * @brief addNode add a possible target
	 * @param receiver the target to Add
	 */
	Switch& addNode(Receiver& receiver);

public:
	Switch();

public slots:
	/**
	 * @brief redirect a message received by socket to right module
	 * @param header a header containing especially a target
	 * @param message the message to send
	 */
	void switchNewMessage(ChatHeader header, QString message);
};

#endif // SWITCH_H
