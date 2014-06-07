#ifndef TOKENCODES_H
#define TOKENCODES_H

#include "Network/Receiver.h"
#include "QtGlobal"

enum class TokenMenuCodes : quint16 {
    UNDEFINED = Receiver::UNDEFINED_CODE,

    ADD_TOKEN
};

#endif // TOKENCODES_H
