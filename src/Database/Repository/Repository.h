#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QString>

#include "Database/QueryBuilder.h"
#include "Database/Database.h"
#include "Database/DBItem.h"

class Repository
{
public:
    Repository() {}
    virtual ~Repository() {}

    virtual const QString getTableName() = 0;

    QueryBuilder findAllQB();

    int insert(DBItem *item, QueryBuilder qb, Database *db);
};

#endif // REPOSITORY_H
