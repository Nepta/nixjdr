#include "QueryBuilder.h"

QueryBuilder::QueryBuilder() {}

QueryBuilder::~QueryBuilder() {}

QSqlQuery QueryBuilder::getQuery() {
    return QSqlQuery(query_);
}

QSqlQuery QueryBuilder::getPreparedQuery() {
    QSqlQuery query;
    query.prepare(query_);

    return query;
}

QString QueryBuilder::getQueryString() {
    return query_;
}

QueryBuilder *QueryBuilder::select(QString arg) {
    query_ = QString("SELECT %1").arg(arg);

    return this;
}

QueryBuilder *QueryBuilder::insertInto(QString table, QStringList cols) {
    QString colsString = cols.join(",");

    QStringList colsVals;
    for (QString col : cols) {
        colsVals.append(":" + col);
    }
    QString colsValsString = colsVals.join(",");

    query_ = QString("INSERT INTO %1 (%2) VALUES (%3)")
             .arg(table)
             .arg(colsString)
             .arg(colsValsString);

    return this;
}


/**
 * @brief QueryBuilder::insertIntoDefault Insert default values into the specified table.
 * @param table table in which the values will be inserted.
 * @return QueryBuilder
 */
QueryBuilder *QueryBuilder::insertIntoDefault(QString table) {
    query_ = QString("INSERT INTO %1 DEFAULT VALUES")
             .arg(table);

    return this;
}

QueryBuilder *QueryBuilder::from(QString from, QString alias) {
    query_ += QString(" FROM %1").arg(from);

    if (!alias.isEmpty()) {
        query_ += QString(" AS %1").arg(alias);
    }

    return this;
}

QueryBuilder *QueryBuilder::where(QString where) {
    query_ += QString(" WHERE %1").arg(where);

    return this;
}

QueryBuilder *QueryBuilder::andWhere(QString where) {
    query_ += QString(" AND %1").arg(where);

    return this;
}

QueryBuilder *QueryBuilder::deleteFrom(QString from) {
    query_ = QString(
        "DELETE FROM %1"
    ).arg(from);

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
