#ifndef REPOSITORYMANAGER_H
#define REPOSITORYMANAGER_H

#include <QHash>
#include <QString>

#include "Database/Repository/Repository.h"

class RepositoryManager
{
public:
    RepositoryManager();
    ~RepositoryManager();

    Repository *getRepositoryByTableName(QString tableName);

private:
    QHash<QString, Repository*> m_Repositories;

    void insertRepository(Repository *repository);
};

#endif // REPOSITORYMANAGER_H
