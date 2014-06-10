#ifndef GAMEOBJECTREPOSITORY_H
#define GAMEOBJECTREPOSITORY_H

#include <QString>

#include "GameObjects/GameObjectType.h"
#include "Repository.h"

class GameObjectRepository : public Repository
{
public:
    GameObjectRepository();
    ~GameObjectRepository();

    const QString getTableName();

    Repository *getRepositoryByGameObjectType(GameObjectType type);

private:
    QHash<GameObjectType, Repository*> m_GameObjectTypeRepo;
};

#endif // GAMEOBJECTREPOSITORY_H
