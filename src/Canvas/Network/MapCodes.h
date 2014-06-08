#ifndef MAPCODES_H
#define MAPCODES_H

#include "Network/Receiver.h"
#include "QtGlobal"

enum class MapCodes : quint16 {
    UNDEFINED = Receiver::UNDEFINED_CODE,

    OPEN_MAP,
    ADD_SPRITE,
    REMOVE_SPRITE,
    REMOVE_ALL_FOW,
    UPDATE_DRAWING_LAYER_PIXMAP,
    PING
};

#endif // MAPCODES_H
