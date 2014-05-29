#include "TokenItem.h"

TokenItem::TokenItem(QString path, QString name, int size) :
    DBItem("sprite")
{
    construct(path, name, size);
}

TokenItem::TokenItem(DBItem item) :
    DBItem("sprite")
{
    QHash<QString, QString> itemHashMap = item.getHashMap();

    QString name = itemHashMap.value("name");
    QString path =  itemHashMap.value("path");
    int size = itemHashMap.value("size").toInt();

    construct(path, name, size);
}

void TokenItem::construct(QString path, QString name, int size) {
    icon_.addFile(path);
    name_ = name;
    size_ = size;

    appendValue("name", name);
    appendValue("path", path);
    appendValue("size", size);
}

QIcon TokenItem::icon() {
	return icon_;
}

QString TokenItem::name() {
	return name_;
}

int TokenItem::size() {
    return size();
}
