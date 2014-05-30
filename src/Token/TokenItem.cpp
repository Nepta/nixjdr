#include "TokenItem.h"

TokenItem::TokenItem(QString path, QString text, int size) :
    DBItem("tokenitem")
{
    construct(path, text, size);
}

TokenItem::TokenItem(DBItem item) :
    DBItem("tokenitem")
{
    QHash<QString, QString> itemHashMap = item.getHashMap();

    int id = itemHashMap.value("id").toInt();
    QString text = itemHashMap.value("text");
    QString path =  itemHashMap.value("path");
    int size = itemHashMap.value("size").toInt();

    construct(id, path, text, size);
}

void TokenItem::construct(int id, QString path, QString text, int size) {
    id_ = id;
    construct(path, text, size);
}

void TokenItem::construct(QString path, QString text, int size) {
    setText(text);
    path_ = path;
    setIcon(QIcon(path));
    size_ = size;
}

QString TokenItem::path() {
    return path_;
}

int TokenItem::size() {
    return size_;
}
