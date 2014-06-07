#ifndef MAPCODES_H
#define MAPCODES_H

#include "QtGlobal"

enum class MapCodes : quint16 {
    UNDEFINED = Receiver::UNDEFINED_CODE,

    OPEN_MAP,
    ADD_SPRITE,
    REMOVE_SPRITE,
    REMOVE_ALL_FOW
};

#endif // MAPCODES_H
