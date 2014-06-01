#ifndef TOKENITEMREPOSITORY_H
#define TOKENITEMREPOSITORY_H

#include "Database/Repository/Repository.h"

#include "Token/TokenItem.h"

class TokenItemRepository : public Repository
{
public:
    TokenItemRepository() {}
    ~TokenItemRepository() {}

    const QString getTableName();

    QueryBuilder getNormalTokenItemsQB();
    QueryBuilder getSpecialTokenItemsQB();

    QList<TokenItem *> getTokenItems(Database *db);
    TokenItem* getFowTokenItem(Database *db);
    int insertTokenItem(TokenItem *tokenItem, Database *db);
};

#endif // TOKENITEMREPOSITORY_H
