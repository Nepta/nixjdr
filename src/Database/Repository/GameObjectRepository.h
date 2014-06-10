#ifndef GAMEOBJECTREPOSITORY_H
#define GAMEOBJECTREPOSITORY_H

#include <QString>

#include "GameObjects/GameObject.h"
#include "GameObjects/GameObjectType.h"
#include "GameObjectSubRepository.h"
#include "Repository.h"

class GameObjectRepository : public Repository
{
public:
    GameObjectRepository();
    ~GameObjectRepository();

    const QString getTableName();

    int insertGameObject(GameObject *gameObject);
    GameObjectSubRepository *getRepositoryByGameObjectType(GameObjectType type);
    GameObject *getGameObjectById(int id);

private:
    QHash<GameObjectType, GameObjectSubRepository*> m_GameObjectTypeRepo;
};

#endif // GAMEOBJECTREPOSITORY_H
