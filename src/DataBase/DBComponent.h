#ifndef DBCOMPONENT_H
#define DBCOMPONENT_H

#include "DataBase.h"

/**
 * @brief A DBComponent can manipulate the application database.
 */
class DBComponent
{
public:
    DBComponent();
    DBComponent(DataBase *db);
    ~DBComponent();

    void setDatabase(DataBase *db);

protected:
    DataBase *db_;
};

#endif // DBCOMPONENT_H
