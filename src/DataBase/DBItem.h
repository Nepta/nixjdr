#ifndef DBITEM_H
#define DBITEM_H
#include <QString>
#include <QList>
#include <QVector>
#include "QueryType.h"

class DBItem{
	QString targetTable_;
	QueryType type_;
	QList<QString> listValue_;

protected:
	int pushDB(QString newValue);
	int pushDB(int newValue);
public:
	DBItem(QueryType::TYPE type);
	QString tableAffected();
	void tableAffected(QString targetTable);
	QString value(int index);
	QString buildQuery();
	QueryType type();
//	virtual QString table() = 0;

};

#endif // DBITEM_H
