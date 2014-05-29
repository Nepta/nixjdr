#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlDatabase>
#include <QFile>
#include <QObject>
#include "QueryBuilder.h"
#include "DBItem.h"
#include "DBItemList.h"

class DataBase : public QObject {
	Q_OBJECT

public:
    DataBase(const QString dbName, const QString& serverAddress, const int &serverPort);
	virtual ~DataBase();
    void push(QueryBuilder queryBuilder);
    QList<DBItem> pull(QueryBuilder queryBuilder);
    DBItem pullFirst(QueryBuilder queryBuilder);

private:
    QSqlDatabase db_;

signals:
	void newItemInDB(DBItem *item);
};

#endif // DATABASE_H
