#include "QueryBuilder.h"

QueryBuilder::QueryBuilder() {}

QueryBuilder::~QueryBuilder() {}

QSqlQuery QueryBuilder::getQuery() {
    return QSqlQuery(query_);
}

QueryBuilder *QueryBuilder::select(QString arg) {
    query_ = QString("SELECT %1").arg(arg);

    return this;
}

QueryBuilder *QueryBuilder::insertInto(QString table) {
    query_ = QString("INSERT INTO %1")
             .arg(table);

    return this;
}

QueryBuilder *QueryBuilder::insertInto(QString table, QString cols) {
    query_ = QString("INSERT INTO %1 (%2)")
             .arg(table)
             .arg(cols);

    return this;
}

QueryBuilder *QueryBuilder::values(QString arg) {
    query_ += QString(" VALUES (%3)").arg(arg);

    return this;
}

QueryBuilder *QueryBuilder::from(QString from, QString alias) {
    query_ += QString(" FROM %1").arg(from);

    if (!alias.isEmpty()) {
        query_ += QString(" AS %1").arg(alias);
    }

    return this;
}
