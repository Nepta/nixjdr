#include "Character.h"

Character::Character(QString name, int maxHp, int hp) :
    GameObject(name, GameObjectType::CHARACTER)
{
    m_MaxHp = maxHp;
    m_Hp = hp;
}

Character::Character(DBItem gameObjectDbItem, DBItem characterDbItem) :
    GameObject(gameObjectDbItem)
{
    columnsValues_ = characterDbItem.getHashMap();

    int maxHp = columnsValues_.value("maxhp").toInt();
    int hp = columnsValues_.value("hp").toInt();

    m_MaxHp = maxHp;
    m_Hp = hp;
}

Character::~Character() {}


int Character::getMaxHp() {
    return m_MaxHp;
}

int Character::getHp() {
    return m_Hp;
}

GameObject *Character::clone() {
    Character *clone = new Character(m_Name, m_MaxHp, m_Hp);

    return clone;
}
