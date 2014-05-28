#ifndef DBITEM_H
#define DBITEM_H
#include <QString>
#include <QList>
#include <QVector>
#include "QueryType.h"

class DBItem{
	QString targetTable_;
	QList<QString> listValue_;

protected:
	int appendValue(QString newValue);
	int appendValue(int newValue);

public:
	DBItem();
	QString tableAffected();
	void tableAffected(QString targetTable);
	QString value(int index);
//	virtual QString table() = 0;

};

#endif // DBITEM_H
