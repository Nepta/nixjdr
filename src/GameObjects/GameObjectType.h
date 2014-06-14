#ifndef GAMEOBJECTTYPE_H
#define GAMEOBJECTTYPE_H

#include <QtGlobal>
#include <QHash>

enum class GameObjectType {
    UNDEFINED = 0,
    CHARACTER
};
inline uint qHash(const GameObjectType &key) { return qHash((int) key); }

#endif // GAMEOBJECTTYPE_H
