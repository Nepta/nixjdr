#include <QSqlRecord>
#include <QSqlTableModel>
#include <QSqlField>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include <QVariant>

#include "Database.h"

Database* Database::m_Instance = NULL;

Database::Database(const QString dbName, const QString& serverAddress, const int& serverPort) {
    db_ = QSqlDatabase::addDatabase("QPSQL");
	db_.setUserName("jdr");
    db_.setDatabaseName(dbName);
	db_.setPassword("password");
    db_.setHostName(serverAddress);
    db_.setPort(serverPort);
	db_.open();
}

Database::~Database(){
	db_.close();
}

Database* Database::instantiate(const QString& dbName, const QString& serverAddress,
    const int& serverPort)
{
    if (!m_Instance) {
        m_Instance = new Database(dbName, serverAddress, serverPort);
    }

    return m_Instance;
}

Database* Database::instance() {
    return m_Instance;
}

/**
 * @brief Database::push Executes the given query. Use this method with queries which do not
 * return a result.
 * @param query Query to execute.
 */
void Database::push(QSqlQuery query) {
    query.exec();
}

/**
 * @brief Database::pushWithId Executes the given query and retrieve the id of the inserted row.
 * Only use this method with queries which are not prepared.
 * @param query Query to execute.
 * @return Id of the inserted row.
 */
int Database::pushWithId(QSqlQuery query) {
    int resultId;

    if (query.next()) {
        resultId = query.value(0).toInt();
    } else {
        resultId = 0;
    }

    return resultId;
}

/**
 * @brief Database::pushPreparedWithId Executes the given query and retrieve the id of the
 * inserted row. Only use this method with prepared queries.
 * @param query Query to execute.
 * @return
 */
int Database::pushPreparedWithId(QSqlQuery query) {
    push(query);

    return pushWithId(query);
}

/**
 * @brief Database::pull Executes the given query and stores the resulting rows in a QList of DBItem.
 * @param query Query to execute
 * @return QList of DBItem containing the resulting rows of the query.
 */
QList<DBItem> Database::pull(QSqlQuery query) {
    QSqlRecord record = query.record(); // holds information about field names
    QList<DBItem> dbItems; // list to populate

    while(query.next()) {
        DBItem item;

        for (int i = 0 ; i < record.count() ; i++) {
            QString fieldName = record.fieldName(i);
            QVariant fieldValue = query.value(i);

            item.appendValue(fieldName, fieldValue);
        }

        dbItems.append(item);
    }

    return dbItems;
}

/**
 * @brief Database::pullFirst Executes the given query and store the first row in a DBItem.
 * @param query Query to execute.
 * @return DBitem containing the first resulting row of the query.
 */
DBItem Database::pullFirst(QSqlQuery query) {
    QSqlRecord record = query.record(); // holds information about field names
    DBItem item; // item to create

    if (query.next()) {
        for (int i = 0 ; i < record.count() ; i++) {
            QString fieldName = record.fieldName(i);
            QVariant fieldValue = query.value(i);

            item.appendValue(fieldName, fieldValue);
        }
    }

    return item;
}
