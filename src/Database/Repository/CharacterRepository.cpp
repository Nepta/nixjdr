#include "RepositoryManager.h"
#include "GameObjectRepository.h"
#include "CharacterRepository.h"

const QString CharacterRepository::getTableName() {
    return "character";
}

/**
 * @brief CharacterRepository::insertCharacter Inserts a Character in the database.
 * @param character The Character to insert in the database.
 * @return ID given by the database to the newly inserted row.
 * @remarks the associated GameObject must already be inserted in the database.
 */
int CharacterRepository::insertCharacter(Character *character) {
    QHash<QString, QVariant> args {
        {"id", character->id()},
        {"maxhp", character->getMaxHp()},
        {"hp", character->getHp()}
    };

    QueryBuilder qb = insertQB(args.keys());
    int idCharacter = insert(character, qb, args);

    return idCharacter;
}

void CharacterRepository::updateCharacter(Character *character) {
    QHash<QString, QVariant> args {
        {"maxhp", character->getMaxHp()},
        {"hp", character->getHp()}
    };

    updateById(character->id(), args);
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

/**
 * @brief CharacterRepository::insertSubGameObject Reimplemented from GameObjectSubRepository.
 * Inserts a Character in the database.
 * @param gameObject object inheriting from Character and downcasted as a GameObject.
 * @return Id of the inserted Character.
 */
int CharacterRepository::insertSubGameObject(GameObject *gameObject) {
    Character *character = dynamic_cast<Character*>(gameObject);

    return insertCharacter(character);
}

