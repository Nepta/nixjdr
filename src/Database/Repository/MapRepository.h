#ifndef MAPREPOSITORY_H
#define MAPREPOSITORY_H

#include <QString>
#include "Database/QueryBuilder.h"
#include "Database/Database.h"
#include "Canvas/Map.h"

class MapRepository
{
public:
    static const QString getTableName();

    static QueryBuilder getMapQB();
    static QueryBuilder insertMapQB(Map *map);

    static int insertMap(Map *map, Database *db);
};

#endif // MAPREPOSITORY_H
