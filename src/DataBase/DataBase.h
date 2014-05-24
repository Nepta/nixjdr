#ifndef DATABASE_H
#define DATABASE_H
#include <QString>
#include <QSqlDatabase>
#include <QFile>
#include "DBItem.h"

class DataBase{
	QString dbName_;
	QSqlDatabase db_;
public:
    DataBase(const QString dbName);
	void addItem(DBItem& item);
	virtual ~DataBase();
	void initDB();
};

#endif // DATABASE_H
