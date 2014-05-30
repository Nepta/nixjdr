#include "DBItem.h"

DBItem::DBItem(QString table, int id) :
    tableName_(table),
    id_(id)
{}

void DBItem::appendValue(QString columName, int newValue){
	appendValue(columName, QString(newValue));
}

void DBItem::appendValue(QString columName, QString newValue){
    columnsValues_.insert(columName, newValue);
}

QHash<QString, QString>& DBItem::getHashMap(){
	return columnsValues_;
}

void DBItem::setId(int id) {
    id_ = id;
}

int DBItem::id() {
    return id_;
}
