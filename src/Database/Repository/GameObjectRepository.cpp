#include "RepositoryManager.h"
#include "GameObjectRepository.h"

GameObjectRepository::GameObjectRepository() {
    m_GameObjectTypeRepo.insert(GameObjectType::CHARACTER, &RepositoryManager::s_CharacterRepository);
}

GameObjectRepository::~GameObjectRepository() {}

const QString GameObjectRepository::getTableName() {
    return "gameobject";
}

Repository *GameObjectRepository::getRepositoryByGameObjectType(GameObjectType type) {
    return m_GameObjectTypeRepo.value(type);
}
