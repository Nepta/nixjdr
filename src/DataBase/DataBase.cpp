#include <QSqlRecord>
#include <iostream>
#include <QSqlTableModel>
#include <QSqlField>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include "DataBase.h"

DataBase::DataBase(const QString dbName, const QString& serverAddress, const int& serverPort) {
	db_ = QSqlDatabase::addDatabase("QPSQL");
	db_.setUserName("jdr");
    db_.setDatabaseName(dbName);
	db_.setPassword("password");
    db_.setHostName(serverAddress);
    db_.setPort(serverPort);
	db_.open();
}

DataBase::~DataBase(){
	db_.close();
}

/**
 * @brief DataBase::push Executes the query given by the QueryBuilder. Use this method with queries
 * which do not return a result.
 * @param queryBuilder
 */
void DataBase::push(QueryBuilder queryBuilder) {
    queryBuilder.getQuery().exec();
}

/**
 * @brief DataBase::pull Executes the query given by the queryBuilder and stores the resulting rows
 * in a QList of DBItem.
 * @param queryBuilder
 * @return QList of DBItem containing the resulting rows of the query.
 */
QList<DBItem> DataBase::pull(QueryBuilder queryBuilder) {
    QSqlQuery query = queryBuilder.getQuery(); // query to execute
    QSqlRecord record = query.record(); // holds information about field names
    QList<DBItem> dbItems; // list to populate

    while(query.next()) {
        DBItem item;

        for (int i = 0 ; i < record.count() ; i++) {
            QString fieldName = record.fieldName(i);
            QString fieldValue = query.value(i).toString();

            item.appendValue(fieldName, fieldValue);
        }

        dbItems.append(item);
    }

    return dbItems;
}

/**
 * @brief DataBase::pullFirst Executes the query given by the queryBuilder and store the first row
 * in a DBItem.
 * @param queryBuilder
 * @return DBitem containing the first resulting row of the query.
 */
DBItem DataBase::pullFirst(QueryBuilder queryBuilder) {
    QSqlQuery query = queryBuilder.getQuery(); // query to execute
    QSqlRecord record = query.record(); // holds information about field names
    DBItem item; // item to create

    if (query.next()) {
        for (int i = 0 ; i < record.count() ; i++) {
            QString fieldName = record.fieldName(i);
            QString fieldValue = query.value(i).toString();

            item.appendValue(fieldName, fieldValue);
        }
    }

    return item;
}
