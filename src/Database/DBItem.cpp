#include "DBItem.h"

DBItem::DBItem(int id) : id_(id) {}

void DBItem::appendValue(QString columName, QVariant newValue) {
    columnsValues_.insert(columName, newValue);
}

QHash<QString, QVariant>& DBItem::getHashMap(){
	return columnsValues_;
}

void DBItem::setId(int id) {
    id_ = id;
}

int DBItem::id() {
    return id_;
}
