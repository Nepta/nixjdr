#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QString>

class Repository
{
public:
    Repository() {}
    virtual ~Repository() {}

    virtual const QString getTableName() = 0;
};

#endif // REPOSITORY_H
