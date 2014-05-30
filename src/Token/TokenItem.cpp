#include "TokenItem.h"

TokenItem::TokenItem(QString path, QString name, int size) :
    DBItem("tokenitem")
{
    construct(path, name, size);
}

TokenItem::TokenItem(DBItem item) :
    DBItem("tokenitem")
{
    QHash<QString, QString> itemHashMap = item.getHashMap();

    int id = itemHashMap.value("id").toInt();
    QString name = itemHashMap.value("name");
    QString path =  itemHashMap.value("path");
    int size = itemHashMap.value("size").toInt();

    construct(id, path, name, size);
}

void TokenItem::construct(int id, QString path, QString name, int size) {
    id_ = id;
    construct(path, name, size);
}

void TokenItem::construct(QString path, QString name, int size) {
    name_ = name;
    path_ = path;
    icon_.addFile(path);
    size_ = size;
}

QIcon TokenItem::icon() {
	return icon_;
}

QString TokenItem::path() {
    return path_;
}

QString TokenItem::name() {
	return name_;
}

int TokenItem::size() {
    return size_;
}
