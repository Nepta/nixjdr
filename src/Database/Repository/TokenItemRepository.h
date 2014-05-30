#ifndef TOKENITEMREPOSITORY_H
#define TOKENITEMREPOSITORY_H

#include <QString>
#include "Database/QueryBuilder.h"
#include "Database/Database.h"
#include "Token/TokenItem.h"

class TokenItemRepository
{
public:
    static const QString getTableName();
    static QueryBuilder getTokenItemsQB();
    static QList<TokenItem> getTokenItems(Database *db);
};

#endif // TOKENITEMREPOSITORY_H
