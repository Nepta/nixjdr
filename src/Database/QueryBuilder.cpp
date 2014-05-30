#include "QueryBuilder.h"

QueryBuilder::QueryBuilder() {}

QueryBuilder::~QueryBuilder() {}

QSqlQuery QueryBuilder::getQuery() {
    return QSqlQuery(query_);
}

QString QueryBuilder::getQueryString() {
    return query_;
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

QueryBuilder *QueryBuilder::values(QList<QString> args) {
    QString concatenatedArgs("");
    bool firstArg = true;

    for (QString arg : args) {
        if (!firstArg) {
            concatenatedArgs += ", ";
        } else {
            firstArg = false;
        }

        concatenatedArgs += QString("'%1'").arg(arg);
    }

    query_ += QString(" VALUES (%1)").arg(concatenatedArgs);

    return this;
}

QueryBuilder *QueryBuilder::from(QString from, QString alias) {
    query_ += QString(" FROM %1").arg(from);

    if (!alias.isEmpty()) {
        query_ += QString(" AS %1").arg(alias);
    }

    return this;
}

void QueryBuilder::withAsSelect(QueryBuilder qb, QString select) {
    query_ = QString(
        "WITH row AS ("
            "%1 RETURNING *"
        ")"
        "SELECT %2 from row"
    ).arg(qb.getQueryString())
     .arg(select);
}
