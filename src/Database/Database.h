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
    Database(const QString dbName, const QString& serverAddress, const int &serverPort);
    virtual ~Database();
    void push(QueryBuilder queryBuilder);
    int pushWithId(QueryBuilder queryBuilder);
    QList<DBItem> pull(QueryBuilder queryBuilder);
    DBItem pullFirst(QueryBuilder queryBuilder);

private:
    QSqlDatabase db_;

signals:
	void newItemInDB(DBItem *item);
};

#endif // DATABASE_H
