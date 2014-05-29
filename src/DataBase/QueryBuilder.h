#ifndef QUERYBUILDER_H
#define QUERYBUILDER_H

#include <QSqlQuery>
#include <QString>

class QueryBuilder {
public:
    QueryBuilder();
    ~QueryBuilder();

    QueryBuilder *select(QString arg);
    QueryBuilder *insertInto(QString table);
    QueryBuilder *insertInto(QString table, QString cols);
    QueryBuilder *values(QString arg);
    QueryBuilder *from(QString arg);

    QSqlQuery getQuery();

private:
    QString query_;
};

#endif // QUERYBUILDER_H
