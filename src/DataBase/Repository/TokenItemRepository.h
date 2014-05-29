#ifndef TOKENITEMREPOSITORY_H
#define TOKENITEMREPOSITORY_H

#include <QString>
#include "DataBase/QueryBuilder.h"

class TokenItemRepository
{
public:
    static const QString getTableName();
    static QueryBuilder getTokenItems();
};

#endif // TOKENITEMREPOSITORY_H
