#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"

class Character : public GameObject
{
public:
    Character();
    ~Character();

private:
    int m_MaxHP;
    int m_HP;
};

#endif // CHARACTER_H
