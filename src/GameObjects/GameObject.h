#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QString>

#include "GameObjectType.h"

class GameObject
{
public:
    GameObject();
    ~GameObject();

private:
    QString m_Name;
    GameObjectType m_Type;
};

#endif // GAMEOBJECT_H
