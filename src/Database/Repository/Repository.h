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

    QueryBuilder findByIdQB(int id);
    QueryBuilder deleteByIdQb(int id);
    QueryBuilder findAllQB();
    QueryBuilder insertQB(QList<QString> cols);

    DBItem findById(int id, Database *db);
    int insert(DBItem *item, QueryBuilder qb, QHash<QString, QVariant> pBindValues, Database *db);
    int insertIntoDefault(DBItem *item, Database *db);
    void deleteById(int id, Database *db);

    void bindValues(QSqlQuery *query, QHash<QString, QVariant> bindValues);
    void bindValue(QSqlQuery *query, const QString& placeholder, const QVariant& val);
};

#endif // REPOSITORY_H
