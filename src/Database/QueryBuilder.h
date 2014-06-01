#ifndef QUERYBUILDER_H
#define QUERYBUILDER_H

#include <QSqlQuery>
#include <QStringList>
#include <QList>
#include <QString>

class QueryBuilder {
public:
    QueryBuilder();
    ~QueryBuilder();

    QueryBuilder *select(QString arg);
    QueryBuilder *insertInto(QString table, QStringList cols);
    QueryBuilder *insertIntoDefault(QString table);
    QueryBuilder *from(QString from, QString alias = "");
    QueryBuilder *where(QString where);
    QueryBuilder *andWhere(QString where);
    void withAsSelect(QueryBuilder qb, QString select);

    QSqlQuery getQuery();
    QSqlQuery getPreparedQuery();
    QString getQueryString();

private:
    QString query_;
};

#endif // QUERYBUILDER_H
