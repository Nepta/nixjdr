#include "RepositoryManager.h"
#include "GameObjectRepository.h"

GameObjectRepository::GameObjectRepository() {
    m_GameObjectTypeRepo.insert(GameObjectType::CHARACTER, &RepositoryManager::s_CharacterRepository);
}

GameObjectRepository::~GameObjectRepository() {}

const QString GameObjectRepository::getTableName() {
    return "gameobject";
}

/**
 * @brief GameObjectRepository::insertGameObject Inserts a full GameObject in the database (data
 * in the GameObject class and data in the class inheriting GameObject).
 * @param gameObject
 * @return Id of the inserted row.
 */
int GameObjectRepository::insertGameObject(GameObject *gameObject) {
    QHash<QString, QVariant> args {
        {"name", gameObject->getName()},
        {"type", (int) gameObject->getType()}
    };

    QueryBuilder qb = insertQB(args.keys());
    int id = insert(gameObject, qb, args);

    // Insert data coming from the class inheriting GameObject
    GameObjectSubRepository *repository = getRepositoryByGameObjectType(gameObject->getType());
    if (repository != NULL) {
        repository->insertSubGameObject(gameObject); // TODO
    }

    return id;
}

/**
 * @brief GameObjectRepository::getRepositoryByGameObjectType Retrieve a GameObjectSubRepository
 * from the specified GameObjectType.
 * @param type GameObjectType associated with the GameObjectSubRepository to get.
 * @return A repository subclassing GameObjectSubRepository.
 */
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
