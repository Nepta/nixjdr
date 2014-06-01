#ifndef MAPREPOSITORY_H
#define MAPREPOSITORY_H

#include <QString>

#include "Database/Repository/Repository.h"
#include "Database/QueryBuilder.h"
#include "Database/Database.h"

#include "Canvas/Map.h"

class MapRepository : public Repository
{
public:
    const QString getTableName();

    QueryBuilder getMapQB();
    QueryBuilder insertMapQB(Map *map);

    int insertMap(Map *map, Database *db);
};

#endif // MAPREPOSITORY_H
