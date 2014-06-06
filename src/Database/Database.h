#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlDatabase>
#include <QFile>
#include <QObject>

#include "QueryBuilder.h"
#include "DBItem.h"
#include "DBItemList.h"

class Database : public QObject {
	Q_OBJECT

public:
    ~Database();

    static Database* instantiate(const QString& dbName, const QString& serverAddress,
                                 const int& serverPort);
    static Database* instance();

    void push(QSqlQuery query);
    int pushWithId(QSqlQuery query);
    int pushPreparedWithId(QSqlQuery query);
    QList<DBItem> pull(QSqlQuery query);
    DBItem pullFirst(QSqlQuery query);

private:
    Database(const QString dbName, const QString& serverAddress, const int &serverPort);
    static Database* m_Instance;

    QSqlDatabase db_;
};

#endif // DATABASE_H
