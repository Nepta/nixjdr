#ifndef MAPREPOSITORY_H
#define MAPREPOSITORY_H

#include <QString>

#include "Database/Repository/Repository.h"
#include "Database/Database.h"

#include "Canvas/Map.h"

class MapRepository : public Repository
{
public:
    MapRepository() {}
    ~MapRepository() {}

    const QString getTableName();

    QueryBuilder insertMapQB(Map *map);

    int insertMap(Map *map, Database *db);
};

#endif // MAPREPOSITORY_H
