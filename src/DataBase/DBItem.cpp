#include "DBItem.h"
#include <QDebug>

DBItem::DBItem(QString table) : targetTable_(table){
}

QString DBItem::tableAffected(){
	return targetTable_;
}

void DBItem::appendValue(QString columName, int newValue){
	appendValue(columName, QString(newValue));
}

void DBItem::appendValue(QString columName, QString newValue){
	columnsValues_.insert(columName, "'" + newValue + "'");
}

QHash<QString, QString>& DBItem::getHashMap(){
	return columnsValues_;
}
