#ifndef GAMEOBJECTSUBREPOSITORY_H
#define GAMEOBJECTSUBREPOSITORY_H

#include "GameObjects/GameObject.h"
#include "Repository.h"

class GameObjectSubRepository : public Repository
{
public:
    GameObjectSubRepository() {}
    virtual ~GameObjectSubRepository() {}

    virtual const QString getTableName() = 0;
    virtual GameObject *getFullGameObject(int id) = 0;
    virtual int insertSubGameObject(GameObject *gameObject) = 0;
};

#endif // GAMEOBJECTSUBREPOSITORY_H
