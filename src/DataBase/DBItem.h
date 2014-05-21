#ifndef DBITEM_H
#define DBITEM_H
#include <QString>
#include <QList>
#include <QVector>

class DBItem{
	QString type_;
	QList<QString> listValue_;

public:
	DBItem(QString type);
	QString type();
	QString value(int index);
	virtual QString table() = 0;
};

#endif // DBITEM_H
