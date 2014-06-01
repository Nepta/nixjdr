#ifndef TOKENITEMREPOSITORY_H
#define TOKENITEMREPOSITORY_H

#include <QString>

#include "Database/Repository/Repository.h"
#include "Database/QueryBuilder.h"
#include "Database/Database.h"

#include "Token/TokenItem.h"

class TokenItemRepository : public Repository
{
public:
    const QString getTableName();

    QueryBuilder getTokenItemsQB();
    QueryBuilder getNormalTokenItemsQB();
    QueryBuilder getSpecialTokenItemsQB();
    QueryBuilder insertTokenItemQB(TokenItem *tokenItem);

    QList<TokenItem *> getTokenItems(Database *db);
    TokenItem* getFowTokenItem(Database *db);
    int insertTokenItem(TokenItem *tokenItem, Database *db);
};

#endif // TOKENITEMREPOSITORY_H
