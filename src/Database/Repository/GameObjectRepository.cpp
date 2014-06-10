#include "RepositoryManager.h"
#include "GameObjectRepository.h"

GameObjectRepository::GameObjectRepository() {
    m_GameObjectTypeRepo.insert(GameObjectType::CHARACTER, &RepositoryManager::s_CharacterRepository);
}

GameObjectRepository::~GameObjectRepository() {}

const QString GameObjectRepository::getTableName() {
    return "gameobject";
}

int GameObjectRepository::insertGameObject(GameObject *gameObject) {
    QHash<QString, QVariant> args {
        {"name", gameObject->getName()},
        {"type", (int) gameObject->getType()}
    };

    QueryBuilder qb = insertQB(args.keys());
    int id = insert(gameObject, qb, args);

    return id;
}

GameObjectSubRepository *GameObjectRepository::getRepositoryByGameObjectType(GameObjectType type) {
    return m_GameObjectTypeRepo.value(type);
}

/**
 * @brief GameObjectRepository::getGameObjectById Retrieve the instance of a class inherithing
 * GameObject by its id (e.g. an instance of Character).
 * @param id Id of the GameObject to retrieve.
 * @return Object from a class inheriting GameObject.
 */
GameObject *GameObjectRepository::getGameObjectById(int id) {
    DBItem gameObjectDbItem = findById(id);
    GameObjectType type = (GameObjectType) gameObjectDbItem.getHashMap().value("type").toInt();

    GameObjectSubRepository *repository = getRepositoryByGameObjectType(type);
    GameObject *gameObject = repository->getFullGameObject(id);

    return gameObject;
}
