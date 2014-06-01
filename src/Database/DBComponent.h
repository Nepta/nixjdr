#ifndef DBCOMPONENT_H
#define DBCOMPONENT_H

#include "Database/Repository/RepositoryManager.h"
#include "Database.h"

/**
 * @brief A DBComponent can manipulate the application database.
 */
class DBComponent
{
public:
    DBComponent();
    DBComponent(Database *db);
    ~DBComponent();

    DBComponent *setDatabase(Database *db);
    DBComponent *setRepositoryManager(RepositoryManager *rm);

protected:
    Database *db_;
    RepositoryManager *rm_;
};

#endif // DBCOMPONENT_H
