#ifndef DBCOMPONENT_H
#define DBCOMPONENT_H

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

protected:
    Database *db_;
};

#endif // DBCOMPONENT_H
