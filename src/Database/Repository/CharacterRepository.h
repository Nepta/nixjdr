#ifndef CHARACTERREPOSITORY_H
#define CHARACTERREPOSITORY_H

#include "Database/Repository/Repository.h"

class CharacterRepository : public Repository
{
public:
    CharacterRepository() {}
    ~CharacterRepository() {}

    const QString getTableName();
};

#endif // CHARACTERREPOSITORY_H
