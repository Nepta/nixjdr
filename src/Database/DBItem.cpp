#include "DBItem.h"

DBItem::DBItem(int id) : id_(id) {}

void DBItem::appendValue(QString columName, QVariant newValue) {
    columnsValues_.insert(columName, newValue);
}

QByteArray DBItem::serialize() {
    QByteArray serializedData;
    QDataStream stream(&serializedData, QIODevice::WriteOnly);

    stream << columnsValues_;

    return serializedData;
}

void DBItem::unserialize(QByteArray& data) {
    QDataStream stream(&data, QIODevice::ReadOnly);

    stream >> columnsValues_;
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
