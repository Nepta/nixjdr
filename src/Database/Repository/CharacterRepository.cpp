#include "RepositoryManager.h"
#include "GameObjectRepository.h"
#include "CharacterRepository.h"

const QString CharacterRepository::getTableName() {
    return "character";
}

/**
 * @brief insertCharacter Inserts a Character and its associated GameObject in the database.
 * @param character The Character to insert in the database.
 * @return ID given by the database to the newly inserted row.
 * @remarks The inserted Character and the associated GameObject have the same Id.
 */
int CharacterRepository::insertCharacter(Character *character) {
    // Inserts the associated GameObject
    int idGameObject = RepositoryManager::s_GameObjectRepository.insertGameObject(character);

    QHash<QString, QVariant> args {
        {"id", idGameObject},
        {"maxhp", character->getMaxHp()},
        {"hp", character->getHp()}
    };

    QueryBuilder qb = insertQB(args.keys());
    int idCharacter = insert(character, qb, args);

    return idCharacter;
}

/**
 * @brief CharacterRepository::getGameObject Retrieve a Character (which inherits GameObject).
 * @param id Id of the Character to retrieve
 * @return A Character (GameObject)
 */
GameObject *CharacterRepository::getFullGameObject(int id) {
    // Retrieve the GameObject part of the object
    DBItem gameObjectDbItem = RepositoryManager::s_GameObjectRepository.findById(id);

    // Retrieve the Character part of the object
    DBItem characterDbItem = findById(id);

    // Constructs the character
    Character *character = new Character(gameObjectDbItem, characterDbItem);

    return character;
}
