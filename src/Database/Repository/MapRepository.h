#ifndef MAPREPOSITORY_H
#define MAPREPOSITORY_H

#include "Database/Repository/Repository.h"

#include "Canvas/Map.h"

class MapRepository : public Repository
{
public:
    MapRepository() {}
    ~MapRepository() {}

    const QString getTableName();

    int insertMap(Map *map);
    Map *findMapById(int id, TokenList *tokenList, Role userRole = Role::ROLE_PLAYER);
};

#endif // MAPREPOSITORY_H
