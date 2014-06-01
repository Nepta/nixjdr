#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QString>

#include "Database/QueryBuilder.h"

class Repository
{
public:
    Repository() {}
    virtual ~Repository() {}

    virtual const QString getTableName() = 0;

    QueryBuilder findAllQB();
};

#endif // REPOSITORY_H
