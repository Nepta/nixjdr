#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QString>
#include <QSqlQuery>
#include <QHash>
#include <QList>
#include <QString>
#include <QVariant>

#include "Database/QueryBuilder.h"
#include "Database/Database.h"
#include "Database/DBItem.h"

class Repository
{
public:
    Repository() {}
    virtual ~Repository() {}

    virtual const QString getTableName() = 0;

    QueryBuilder updateByIdQB(int id, QList<QString> cols);
    QueryBuilder findByIdQB(int id);
    QueryBuilder deleteByIdQb(int id);
    QueryBuilder findAllQB();
    QueryBuilder insertQB(QList<QString> cols);

    DBItem findById(int id);
    void updateById(int id, QHash<QString, QVariant> pBindValues);
    int insert(DBItem *item, QueryBuilder qb, QHash<QString, QVariant> pBindValues);
    int insertIntoDefault(DBItem *item);
    void deleteById(int id);

    void bindValues(QSqlQuery *query, QHash<QString, QVariant> bindValues);
    void bindValue(QSqlQuery *query, const QString& placeholder, const QVariant& val);
};

#endif // REPOSITORY_H
