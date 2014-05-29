#ifndef DATABASE_H
#define DATABASE_H
#include <QString>
#include <QSqlDatabase>
#include <QFile>
#include <QObject>
#include "DBItem.h"

class DataBase : public QObject {
	Q_OBJECT

	QSqlDatabase db_;

public:
    DataBase(const QString dbName, const QString& serverAddress, const int &serverPort);
	virtual ~DataBase();
	void addItem(DBItem& item);

signals:
	void newItemInDB(DBItem *item);
};

#endif // DATABASE_H
