#ifndef DBITEM_H
#define DBITEM_H
#include <QString>
#include <QList>
#include <QVector>
#include "QueryType.h"
#include <QHash>

class DBItem{
	QString targetTable_;
	QHash<QString, QString> columnsValues_;

protected:
	void appendValue(QString columName,QString newValue);
	void appendValue(QString columName, int newValue);

public:
	DBItem(QString table);
	QString tableAffected();
	QHash<QString, QString>& getHashMap();
};

#endif // DBITEM_H
