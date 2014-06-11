#ifndef CHARACTERREPOSITORY_H
#define CHARACTERREPOSITORY_H

#include "GameObjects/Character.h"
#include "GameObjectSubRepository.h"

class CharacterRepository : public GameObjectSubRepository
{
public:
    CharacterRepository() {}
    ~CharacterRepository() {}

    const QString getTableName();

    int insertCharacter(Character *character);
    GameObject *getFullGameObject(int id);
    int insertSubGameObject(GameObject *gameObject);
};

#endif // CHARACTERREPOSITORY_H
