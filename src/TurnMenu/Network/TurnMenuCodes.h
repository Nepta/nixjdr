#ifndef TURNMENUCODES_H
#define TURNMENUCODES_H

#include "Network/Receiver.h"
#include "QtGlobal"

enum class TurnMenuCodes : quint16 {
    UNDEFINED = Receiver::UNDEFINED_CODE,

    UPDATE_TURN
};

#endif // TURNMENUCODES_H
