#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QString>

#include "Database/DBItem.h"
#include "GameObjectType.h"

class GameObject : public DBItem
{
public:
    GameObject(QString name, GameObjectType type);
    GameObject(DBItem item);
    ~GameObject();

    QString getName();
    GameObjectType getType();
    virtual GameObject *clone();

protected:
    QString m_Name;
    GameObjectType m_Type;
};

#endif // GAMEOBJECT_H
