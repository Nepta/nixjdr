#ifndef DATABASE_H
#define DATABASE_H
#include <QString>
#include <QSqlDatabase>
#include <QFile>
#include <QObject>
#include "DBItem.h"

class DataBase : public QObject{
	Q_OBJECT

	QString dbName_;
	QSqlDatabase db_;

public:
	DataBase(const QString dbName, const QString& serverIpAddress);
	void addItem(DBItem& item);
	virtual ~DataBase();
	void initDB();

signals:
	void newItemInDB(DBItem *item);
};

#endif // DATABASE_H
