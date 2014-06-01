#include "Repository.h"

/**
 * @brief Repository::findAllQB Constructs a query to retrieve all the rows from the child's
 * Repository associated table.
 * @return QueryBuilder
 */
QueryBuilder Repository::findAllQB() {
    QueryBuilder qb;
    qb.select("*")->from(getTableName());

    return qb;
}
