#ifndef CHARACTER_H
#define CHARACTER_H

#include "Database/DBItem.h"
#include "GameObject.h"

class Character : public GameObject
{
public:
    Character(QString name, int maxHp, int hp);
    Character(DBItem gameObjectDbItem, DBItem characterDbItem);
    ~Character();

    int getMaxHp();
    int getHp();

    GameObject *clone();

private:
    int m_MaxHp;
    int m_Hp;
};

#endif // CHARACTER_H
