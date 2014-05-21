#ifndef DATABASE_H
#define DATABASE_H
#include <QString>
#include <QSqlDatabase>
#include <QFile>

class DataBase{
	QString dbName_;
	QSqlDatabase db_;
public:
	DataBase(const QString dbName);
	virtual ~DataBase();
};

#endif // DATABASE_H
