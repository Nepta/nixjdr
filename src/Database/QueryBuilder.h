#ifndef QUERYBUILDER_H
#define QUERYBUILDER_H

#include <QSqlQuery>
#include <QList>
#include <QString>

class QueryBuilder {
public:
    QueryBuilder();
    ~QueryBuilder();

    QueryBuilder *select(QString arg);
    QueryBuilder *insertInto(QString table);
    QueryBuilder *insertInto(QString table, QString cols);
    QueryBuilder *values(QList<QString> args);
    QueryBuilder *from(QString from, QString alias = "");
    void withAsSelect(QueryBuilder qb, QString select);

    QSqlQuery getQuery();
    QString getQueryString();

private:
    QString query_;
};

#endif // QUERYBUILDER_H
