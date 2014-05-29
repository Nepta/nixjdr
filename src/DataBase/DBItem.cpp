#include "DBItem.h"

DBItem::DBItem(QString table) : tableName_(table) {}

void DBItem::appendValue(QString columName, int newValue){
	appendValue(columName, QString(newValue));
}

void DBItem::appendValue(QString columName, QString newValue){
    columnsValues_.insert(columName, newValue);
}

QHash<QString, QString>& DBItem::getHashMap(){
	return columnsValues_;
}
