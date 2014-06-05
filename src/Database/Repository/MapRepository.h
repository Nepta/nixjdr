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

    int insertMap(Map *map, Database *db);
    Map *findMapById(int id, Database *db);
};

#endif // MAPREPOSITORY_H
