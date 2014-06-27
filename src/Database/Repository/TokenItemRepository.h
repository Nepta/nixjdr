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

    QList<TokenItem *> getTokenItems();
    TokenItem* getFowTokenItem();
    TokenItem* getTokenItemById(int id);
    int insertTokenItem(TokenItem *tokenItem);

    void updateTokenItem(TokenItem *tokenItem);
};

#endif // TOKENITEMREPOSITORY_H
